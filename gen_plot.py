import matplotlib.pyplot as plt
import copy

def read_data(file_name):
    return_list = []   
    entry = {
        "time": "",
        "name": "",
        "graphics clock": "",
        "memory clock": "",
        "decoder clock": "",
        "fan speed": "",
        "temperature": "",
        "total memory": "",
        "used memory": "",
        "free memory": "",
    }
    with open(file_name, 'r') as f:
        data = f.readlines()
        for line in data:
            split_list = line.split("|")
            entry["time"] = split_list[0].strip()
            entry["name"] = split_list[1].strip()
            entry["graphics clock"] = split_list[2].split(":")[1].strip()
            entry["memory clock"] = split_list[3].split(":")[1].strip()
            entry["decoder clock"] = split_list[4].split(":")[1].strip()
            entry["fan speed"] = split_list[5].split(":")[1].strip()
            entry["temperature"] = split_list[6].split(":")[1].strip()
            entry["total memory"] = split_list[7].split(":")[1].strip()
            entry["used memory"] = split_list[8].split(":")[1].strip()
            entry["free memory"] = split_list[9].split(":")[1].strip()
            return_list.append(copy.deepcopy(entry))
            print(return_list)
    return return_list

read_data("nvml_test.log")
