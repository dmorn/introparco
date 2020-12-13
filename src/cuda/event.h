#ifdef __cplusplus
extern "C" {
#endif

typedef struct Event Event;
struct Event {
	cudaEvent_t tic, toc;
};

void start(Event *e, cudaStream_t s);
float stop(Event *e, cudaStream_t s);
void freeevent(Event *e);
Event* newevent(void);

#ifdef __cplusplus
}
#endif
