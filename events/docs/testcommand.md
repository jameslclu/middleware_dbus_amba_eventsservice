# Get API Version
dbus-send --system --print-reply --dest=fxn.camera.events /fxn/camera/events org.freedesktop.DBus.Properties.Get string:fxn.camera.events string:Version

# Get Events
dbus-send --system --type=method_call --print-reply --dest=fxn.camera.events /fxn/camera/events fxn.camera.events.GetEvents string:'{"volume":5}'

dbus-send --system --type=signal com.camera.ai.onAIEvent string:"hello"
/com/dbus/app com.dbus.signal.to.gui.configuration_code_result int32:11

dbus-send --system --type=signal --print-reply /com/camera.ai com.camera.ai.onAIEvent string:"hello"