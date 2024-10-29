from threading import Semaphore, Thread
from time import sleep

CAPACITY=10
buffer=[-1 for i in range(CAPACITY)]
in_count=0
out_count=0
mutex=Semaphore(1)
empty=Semaphore(CAPACITY)
full=Semaphore(0)

class Producer(Thread):
    def run(self):
        global CAPACITY, buffer, in_count,out_count,mutex,full,empty

        items_produced=0
        counter=0

        while items_produced<20:
            empty.acquire()
            mutex.acquire()

            counter+=1
            buffer[in_count]=counter
            in_count=(in_count+1)%CAPACITY
            print("Producer produced: ",counter)
            
            full.release()
            mutex.release()

            sleep(1)

            items_produced+=1

class Consumer(Thread):
    def run(self):
        global CAPACITY, buffer, in_count,out_count,mutex,empty,full

        items_consumed=0

        while items_consumed<20:
            full.acquire()
            mutex.acquire()

            item=buffer[out_count]
            out_count=(out_count+1)%CAPACITY
            print("Consumer consumed item: ",item)

            empty.release()
            mutex.release()
            sleep(2)
            items_consumed+=1

producer=Producer()
consumer=Consumer()

producer.start()
consumer.start()

producer.join()
consumer.join()


