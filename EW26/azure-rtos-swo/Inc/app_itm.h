#ifndef _TX_ITM_H_
#define _TX_ITM_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* TX ITM macros */
#define ITM_DATA_TRACE_CHANNEL   (1)
#define ITM_THREADID_CHANNEL     (2)
#define ITM_QUEUE_CHANNEL        (3)
#define ITM_SEMAPHORE_CHANNEL    (4)

/* TX ITM functions */
void itmDataTrace(unsigned int *);

void itmQueueIncrement();
void itmQueueDecrement();

void itmSemaphoreIncrement();
void itmSemaphoreDecrement();

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _TX_ITM_H_ */