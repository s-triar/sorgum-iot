create venv `py -3 -m venv venv`
activate venv /venv/Scripts/Activate.ps1
install requirements `pip install -r requirements.txt`
run `flask --app app run --host=0.0.0.0`
run without flask `waitress-serve --listen=127.0.0.1:5000 app:app`

for unexplainable reason, netifaces can not be installed via pip. You can download here https://www.lfd.uci.edu/~gohlke/pythonlibs/#netifaces
and then install it with `pip install name_package_whl`

For check camera list in your device.
- windows:
 cmd -> `ffmpeg -list_devices true -f dshow -i dummy`
        `ffmpeg -f dshow -list_options true -i video="Camera Name"`
- linux/rpi:
 terminal -> `v4l2-ctl --list-devices`
             `v4l2-ctl --device=/dev/video0 --list-formats-ex`