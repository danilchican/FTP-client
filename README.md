# FTP-client
FTP-client based on winSocket for Windows

## Install
Clone the repo via git:
```
$ git clone https://github.com/danilchican/FTP-client.git
```

Add files to the Visual Studio project and compile programm.

## Available client commands
* connect - Create connection to your host
* disconnect - Destroy created session
* pwd - Print working directory
* mkdir [name] - Create new directory
* rmdir [name] - Deletes the named directory on the remote host
* rm [file] - Deletes the named file on the remote host
* rn [from] [to] - Rename the file on the remote host
* download [file] [path] - Download the file from the remote host
* upload [file] [path] - Upload the file from client to the remote host
* cd - Change current directory
* up - Moves up to the parent directory
* ls - Diplay the contents of a current directory
* help - Display available commands
* clear - Clear console screen
* exit - Exit from programm

## Credits
* [Vladislav Danilchik](https://github.com/danilchican)
