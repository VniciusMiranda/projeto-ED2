import os
import sys
import time

class colors:
    OK = '\033[92m' #GREEN
    WARNING = '\033[93m' #YELLOW
    FAIL = '\033[91m' #RED
    RESET = '\033[0m' #RESET COLOR

project_dir = "projeto-ED2" 
dependencies = "curl libcurl4-openssl-dev libncurses5-dev libncursesw5-dev make"


def print_log(message, color=colors.OK):
    print(f"{color}{get_script_suffix()}{message}{colors.RESET}")

def get_script_suffix():
    return f"script({time.asctime(time.localtime())}):"


def main(args):
    if project_dir not in os.getcwd():
        print_log(f"the script must be run inside the dir {project_dir}", colors.FAIL)
        print_log("exiting.", colors.FAIL)
        exit()
        
    print_log("updating and upgrading packages")
    os.system(f"sudo apt update && sudo apt upgrade")

    print_log("installing dependencies...")
    os.system(f"sudo apt install -y {dependencies}")

    print_log("compilling project...")
    os.system("make")

    print_log("setup finished. Run the command 'make run' to use the application.")

if __name__ == "__main__":
    main(sys.argv)








