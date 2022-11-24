
#ifndef _RECORDINGMANAGER_H_
#define _RECORDINGMANAGER_H_

enum event_type_enum {
  EVENT_NONE = 0,
  EVENT_PIR = 1,
  EVENT_AI = 2,
  EVENT_CHIME = 3
};

int set_local_recording_mode(int mode);
int get_local_recording_mode(int &mode);
int event_trigger_recording( int event_type );
int sdcard_full_process(int state);
int recording_service_api_init( void );
int recording_service_api_deinit( void );

#endif /* _RECORDINGMANAGER_H_ */
