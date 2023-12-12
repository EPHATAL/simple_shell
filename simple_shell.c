import os
import sys
import subprocess

def execute_command(command):
    try:
        subprocess.run(command, shell=True, check=True)
    except subprocess.CalledProcessError as e:
        print(f"Error: {e}")
    except Exception as e:
        print(f"An unexpected error occurred: {e}")

def main():
    while True:
        user_input = input("shell> ").strip()

        if user_input.lower() in ["exit", "quit"]:
            break

        try:
            # Use subprocess to run the command
            execute_command(user_input)
        except Exception as e:
            print(f"Error: {e}")

if __name__ == "__main__":
    main()

