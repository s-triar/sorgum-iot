create venv `py -3 -m venv venv`
install requirements `pip install -r requirements.txt`
run `flask --app app run --host=0.0.0.0`
run without flask `waitress-serve --listen=127.0.0.1:5000 app:app`