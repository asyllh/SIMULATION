#Simulation python code from Geraint Palmer

import random #generate random numbers

arrival_rate = 10.0 #double
number_of_servers = 3 #int
service_rate = 4.0 #double
max_simulation_time = 800 #double
warmup = 100
num_trials = 20 #int

def run_trial(seed, arrival_rate, service_rate, number_of_servers, max_simulation_time, warmup):
    random.seed(seed) #seed the random value
    records = [] #'list' (vector)
    servers_end = [0 for server in range(number_of_servers)] #list, initially with elements of value zero for number of servers (in this case, push back three zeros)
    arrival_date = 0.0 #double
    while arrival_date < max_simulation_time: #loop
        arrival_date += random.expovariate(arrival_rate) #part of stop criterion for loop
        service_time = random.expovariate(service_rate) #double
        service_start_date = max(arrival_date, min(servers_end)) #double
        service_end_date = service_start_date + service_time #double
        wait = service_start_date - arrival_date #double
        servers_end.append(service_end_date) #push back service end list
        servers_end = sorted(servers_end)[-number_of_servers:] #delete the smallest of the three values in the list
        records.append((arrival_date, wait)) #matrix, first element arrival date, second element wait value
    waits = [r[1] for r in records if r[0] > warmup] #list, push back wait value if arrival date is larger than warmp time
    return sum(waits) / len(waits) # total of values in waits list / size of waits list

mean_waits = [] #empty list
for seed in range(num_trials): # from 0 to num trials
    mean_waits.append(run_trial(seed, arrival_rate, service_rate, number_of_servers, max_simulation_time, warmup)) #push back value of return from function

print(sum(mean_waits) / len(mean_waits)) #print total of values in mean waits / size of mean weights

'''
random.expovariate is equal to -log(x)/L, x is a random value between 0 and 1, L is the parameter (arrival rate or service rate)
'''