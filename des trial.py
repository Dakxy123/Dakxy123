import simpy
import numpy as np
import random

# Settings
simulation_time = 20  # Total minutes
time = 0
queue = []
server_busy = False
next_arrival = random.randint(1, 4)
next_departure = -1

while time <= simulation_time:
    print(f"Minute {time}")

    # New customer arrives
    if time == next_arrival:
        print(" - Customer arrived")
        if not server_busy:
            service_time = random.randint(2, 5)
            next_departure = time + service_time
            server_busy = True
            print(f"   > Served immediately. Will leave at minute {next_departure}")
        else:
            queue.append(time)
            print(f"   > Joined the queue. Queue length: {len(queue)}")
        next_arrival = time + random.randint(1, 4)

    # Customer finishes service
    if time == next_departure:
        print(" - Customer finished service")
        if queue:
            person = queue.pop(0)
            service_time = random.randint(2, 5)
            next_departure = time + service_time
            print(f"   > Next person from queue is being served. Leaves at {next_departure}")
        else:
            server_busy = False
            next_departure = -1
            print("   > Teller is now free")

    time += 1
