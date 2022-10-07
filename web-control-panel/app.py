from cgi import test
from flask import Flask, request, render_template
from bs4 import BeautifulSoup

def __init__(self):
    app.jinja_env.globals.update(create_waypoint_list=create_waypoint_list)

    app = Flask(__name__)

    def create_waypoint_list(filename):
        #extract coordinates from gpx file
        with open(filename, 'r') as f:
            data = f.read()
        soup = BeautifulSoup(data, 'xml')
        waypoints = soup.find_all('wpt')
        waypoints_list = []
        for waypoint in waypoints:
            waypoints_list.append((waypoint['lat'], waypoint['lon']))
        return waypoints_list

    def build_waypoint_string(waypoint_list):
        #build string for google maps api
        waypoint_string = ''
        for waypoint in waypoint_list:
            waypoint_number = str(waypoint_list.index(waypoint) + 1)
            waypoint_string += waypoint_number + ":" + waypoint[0] + ',' + waypoint[1] + ";"
        return waypoint_string[:-1]

@app.route('/')
def index():
    return render_template('index.html')

print(build_waypoint_string(create_waypoint_list('redlining.gpx')))