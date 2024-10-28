import socket
import pickle
import tkinter as tk
import struct
from tkinter import scrolledtext, messagebox

class RemoteControlClient:
    def __init__(self, master):
        self.master = master
        self.master.title("Remote Control Client")
        self.master.geometry("400x450")

        self.output_area = scrolledtext.ScrolledText(master, wrap=tk.WORD, width=50, height=20)
        self.output_area.pack(pady=10)

        self.command_entry = tk.Entry(master, width=50)
        self.command_entry.pack(pady=10)

        self.send_button = tk.Button(master, text="Send Command", command=self.send_command)
        self.send_button.pack(pady=5)
    
    def send_command(self):
        command = self.command_entry.get()
        if command.lower() == "exit":
            self.master.quit()
            return

        response = self.send_to_server(command)
        # If the command was a screenshot, save the image
        if command == "screenshot" and response:
            if len(response) > 0:
                try:
                    with open("received_screenshot.png", "wb") as f:
                        f.write(response)
                    self.output_area.insert(tk.END, f"Screenshot saved as 'received_screenshot.png'.\n")
                except Exception as e:
                    self.output_area.insert(tk.END, f"Error saving screenshot: {str(e)}\n")
            else:
                self.output_area.insert(tk.END, "No data received for screenshot.\n")
        elif response:
            self.output_area.insert(tk.END, f"Command: {command}\nResponse: {response}\n\n")
        self.command_entry.delete(0, tk.END)

    def send_to_server(self, command):
        try:
            client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            client.connect(("10.253.0.167", 9999))  # Thay SERVER_IP_ADDRESS bằng địa chỉ IP của SERVER
            client.settimeout(10)  # Set a 10-second timeout for receiving data
            client.send(command.encode())
            
            # Receive the screenshot if the command is 'screenshot'
            if command == "screenshot":
                raw_data_length = client.recv(4)  # First 4 bytes contain the length
                if not raw_data_length:
                    return "Fail to save image"
                data_length = struct.unpack('!I', raw_data_length)[0]
                
                # Now receive the actual image data
                data = b""
                while len(data) < data_length:
                    packet = client.recv(4096)
                    if not packet:
                        break
                    data += packet
                messagebox.showerror("Error", data)
                client.close()
                return data  # Return the raw image data
                
            response = receive_data(client)
            return response
        except socket.timeout:
            print(f"Command: {command}\nError: The server took too long to respond.")
            # messagebox.showerror("Error", "The server took too long to respond.")
            return f"Command: {command}\nError: The server took too long to respond."
        except socket.error as e:
            print(f"Command: {command}\nSocket error: {e}")
            return f"Command: {command}\nSocket error: {e}"
        except Exception as e:
            print(f"Command: {command}\nError: {e}")
            return f"Command: {command}\nError: {e}"
        finally:
            client.close()

def receive_data(sock):
    # First, receive the length of the data
    raw_data_length = sock.recv(4)
    if not raw_data_length:
        return None
    data_length = struct.unpack('!I', raw_data_length)[0]

    # Now receive the actual data in chunks
    data = b""
    while len(data) < data_length:
        packet = sock.recv(4096)
        if not packet:
            break
        data += packet
    return pickle.loads(data)

if __name__ == "__main__":
    root = tk.Tk()
    client_app = RemoteControlClient(root)
    root.mainloop()
