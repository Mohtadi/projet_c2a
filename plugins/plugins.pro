TEMPLATE    = subdirs

DIRECTORIES = ./pluginSerialPort \
              ./pluginGPS \
              ./pluginCANGine \
              ./pluginD-Notex20Disk \
              ./pluginGPRS \
              ./pluginBluetooth \
              ./pluginNetwork \
              ./pluginCorsair

SUBDIRS += $$DIRECTORIES



#for(dir, DIRECTORIES) {
#    exists($$dir) {
#        SUBDIRS += $$dir
#    }
#}
