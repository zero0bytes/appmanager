# appmanager
Light weight daemon for checking if given application is running
if not then execute it, its created for raspberry pi to monitoring
applications live:) there is initial version i made some
testing under raspbian stretch.

example output from terminal:  ./appmanager   

Welcome to appmanager v 1.0
Setup...
Initialize timer...


Usage:   appmanager app-name app-path app-param1 app-param2

Example: appmanager nginx /usr/sbin/nginx -v -something

