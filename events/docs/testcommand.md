# Get API Version
dbus-send --system --print-reply --dest=fxn.camera.events /fxn/camera/events org.freedesktop.DBus.Properties.Get string:fxn.camera.events string:Version

# Get Events
dbus-send --system --type=method_call --print-reply --dest=fxn.camera.events /fxn/camera/events fxn.camera.events.GetEvents string:'{"volume":5}'

