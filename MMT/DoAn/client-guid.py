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

        # Create buttons for specific actions
        self.screenshot_button = tk.Button(master, text="Take Screenshot", command=self.take_screenshot)
        self.screenshot_button.pack(pady=5)

        self.copy_file_button = tk.Button(master, text="Copy File", command=self.copy_file)
        self.copy_file_button.pack(pady=5)

        self.delete_file_button = tk.Button(master, text="Delete File", command=self.delete_file)
        self.delete_file_button.pack(pady=5)

        self.exit_button = tk.Button(master, text="Exit", command=self.master.quit)
        self.exit_button.pack(pady=5)

    def send_command(self, command):
        response = self.send_to_server(command)
        self.process_response(response)

    def take_screenshot(self):
        self.send_command("screenshot")

    def copy_file(self):
        # Ask for source and destination
        source = self.command_entry.get()  # Assume source path is entered in the entry box
        destination = "D:\\note\\loc\\"  # Set a fixed destination for example
        command = f"copy_file {source} {destination}"
        self.send_command(command)

    def delete_file(self):
        file_path = self.command_entry.get()  # Assume the file path is entered in the entry box
        command = f"delete_file {file_path}"
        self.send_command(command)

    def send_to_server(self, command):
        try:
            client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            client.connect(("10.253.0.167", 9999))  # Replace with your server IP address
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
                client.close()
                return data  # Return the raw image data

            response = self.receive_data(client)
            client.close()
            return response
        except socket.timeout:
            print(f"Error: The server took too long to respond.")
            return None
        except socket.error as e:
            print(f"Socket error: {e}")
            return None
        except Exception as e:
            print(f"Error: {e}")
            return None
        finally:
            client.close()

    def receive_data(self, sock):
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

    def process_response(self, response):
        if isinstance(response, bytes):
            with open("received_screenshot.png", "wb") as f:
                f.write(response)
            self.output_area.insert(tk.END, "Screenshot saved as 'received_screenshot.png'.\n")
        elif response:
            self.output_area.insert(tk.END, f"Response: {response}\n\n")

if __name__ == "__main__":
    root = tk.Tk()
    client_app = RemoteControlClient(root)
    root.mainloop()
