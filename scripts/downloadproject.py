import urllib
import json
import argparse
import os
import os.path

parser = argparse.ArgumentParser(description='Download a zeega.org project')
parser.add_argument('project', metavar='P', type=str, nargs='+', help='JSON file with project data')
parser.add_argument('destination', metavar='D', type=str, nargs='+', help='Destination folder')

args = parser.parse_args()

destination = args.destination[0]
project_file_path = args.project[0]

#os.mkdir(destination)

json_data = open(project_file_path)
data = json.load(json_data)
f_error = open('error.txt','w')

for layer in data["layers"]:
    print type(layer)
    if "url" in layer["attr"]:
        url = layer["attr"]["url"]
        
        print "Fetching {0}".format(url)
        if "api.soundcloud.com" in url:
        	file_name = url.split("/")[4] + ".mp3"
        else:
        	file_name = url.split('/')[-1]
        
        layer["attr"]["localurl"] = destination + file_name
        	
        try:
            if not os.path.exists(destination + file_name ):
    	        urllib.urlretrieve(url,destination + file_name)
    	        urllib.urlcleanup()
        	print "{0} downloaded successfully".format(url)
        except:
        	print "{0} failed to download".format(file_name)
        	f_error.write("{0} failed \n".format(url))

updated_project_file = open(destination + "zeega_project.json", 'w')
with open(destination + 'zeega_project.json', mode='w') as f:
    json.dump(data, f)

f_error.close()