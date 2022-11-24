#include <sys/syslog.h>

#include "EventsRepository.h"
#include "EventsService.h"
#include "EventsServiceStub.h"

#include "AIServiceProxy.h"

#include "MISCServiceProxy.h"

int main (int argc, char *argv[]) {
    openlog("fxnevents", (LOG_CONS | LOG_PID | LOG_PERROR), LOG_USER);

    LocalDataSource localDataSource;

    EventsRepository eventsRepository(&localDataSource);

    AIServiceProxy aiServiceProxy;
    MISCServiceProxy miscServiceProxy;

    EventsService eventsService(&eventsRepository);
    eventsService.Init();



    EventsServiceStub eventsServiceStub(&eventsService);
    eventsServiceStub.Init();

    eventsServiceStub.Deinit();

    closelog();
    return 0;
}