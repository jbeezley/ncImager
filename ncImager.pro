TEMPLATE = subdirs
CONFIG += ordered
SUBDIRS = lib app
app.depends = lib
