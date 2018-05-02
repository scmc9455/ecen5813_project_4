#*********************************************************************************************
#@file - logger_conversion.py
#@brief - logger_conversion.py file is the python file for the conversion of the log file
#
#@author - Scott McElroy
#
#@date - April 29, 2018
#
#Created for ECEN5813
#**********************************************************************************************/
#
#
#*********************************************************************************************
#@brief- this function returns the log_id of the packet
#
#@param- packet: contents of the first character in the packet
#@return- log_id: returns the log it of the packet
#*********************************************************************************************
def log_type(packet):
    if(packet == 0):
        return "SYSTEM_ID"
    elif(packet == 1):
        return "SYSTEM_VERSION"
    elif(packet == 2):
        return "LOGGER_INITIALIZED"
    elif(packet == 3):
        return "SYSTEM_INITIALIZED"
    elif(packet == 4):
        return "GPIO_INITIALIZED"
    elif(packet == 5):
        return "SYSTEM_HALTED"
    elif(packet == 6):
        return "INFO"
    elif(packet == 7):
        return "WARNING"
    elif(packet == 8):
        return "ERROR"
    elif(packet == 9):
        return "PROFILING_STARTED"
    elif(packet == 10):
        return "PROFILING_RESULT"
    elif(packet == 11):
        return "PROFILING_COMPLETED"
    elif(packet == 12):
        return "DATA_RECEIVED"
    elif(packet == 13):
        return "DATA_ANALYSIS_STARTED"
    elif(packet == 14):
        return "DATA_ALPHA_COUNT"
    elif(packet == 15):
        return "DATA_NUMERIC_COUNT"
    elif(packet == 16):
        return "DATA_PUNCTUATION_COUNT"
    elif(packet == 17):
        return "DATA_MISC_COUNT"
    elif(packet == 18):
        return "DATA_ANALYSIS_COMPLETED"
    elif(packet == 19):
        return "HEARTBEAT"
    elif(packet == 20):
        return "CORE_DUMP"

#*********************************************************************************************
#@brief- this function prints out the module_id of the packet
#
#@param- packet: contents of the second character in the packet
#@return- module_id in a string
#*********************************************************************************************
def module_type(packet):
    if(packet == 0):
        return "PROJECT_4"
    elif(packet == 1):
        return "TEST"

#*********************************************************************************************
#@brief- this function is to print an item from the logger
#
#@param- line_data: this is the packet item to be sent to the function
#@param- n: value to be used for address
#@return- logaddr2: value to be return (pointer of the address need to use in a loop)
#*********************************************************************************************
def item_decode(line_data):
    #packet decoding from the log file      
    first_char = line_data[0]
    second_char = line_data[1]

    #log_id and module_id variables
    log_id = log_type(int(first_char,16))
    module_id = module_type(int(second_char,16))

    #decode the timestamp
    time1 = line_data[2]
    time2 = line_data[3]
    time3 = line_data[4]
    time4 = line_data[5]
    timestamp = [time4, time3, time2, time1]
    timestamp = ''.join(timestamp)
    timestamp = int(timestamp,16)

    #detemine and capture log length
    log_len1 = line_data[6]
    log_len2 = line_data[7]
    log_len3 = line_data[8]
    log_len4 = line_data[9]
    log_len = [log_len4, log_len3, log_len2, log_len1]
    log_len = ''.join(log_len)
    log_len = int(log_len,16)
    #move the log pointer
    logaddr = (10) + log_len

    if (logaddr > (10)):
        payload = line_data[(10):logaddr]
        payload = ''.join(payload)
        payload = int(payload,16)
    else:
        payload = "No Payload"

    #checksum value
    checksum1 = line_data[(logaddr)]
    checksum2 = line_data[(logaddr+1)]
    checksum3 = line_data[(logaddr+2)]
    checksum4 = line_data[(logaddr+3)]
    checksum = [checksum4, checksum3, checksum2, checksum1]
    checksum = ''.join(checksum)
    checksum = int(checksum,16)

    print timestamp,"ns :",log_id," ",module_id,":",payload,"-checksum:",checksum
    print ""
    return

#*********************************************************************************************
#@brief- this function is to print an item from the logger that is in the string format
#
#@param- line_data: this is the packet item to be sent to the function
#@param- n: value to be used for address
#@return- logaddr2: value to be return (pointer of the address need to use in a loop)
#*********************************************************************************************
def item_string(line_data):
    #packet decoding from the log file      
    first_char = int(line_data[0])
    second_char = int(line_data[1])

    #log_id and module_id variables
    log_id = log_type(first_char)
    module_id = module_type(second_char)

    #decode the timestamp
    time1 = line_data[2]
    time2 = line_data[3]
    time3 = line_data[4]
    time4 = line_data[5]
    timestamp = [time4, time3, time2, time1]
    timestamp = ''.join(timestamp)
    timestamp = int(timestamp,16)

    #detemine and capture log length
    log_len1 = line_data[6]
    log_len2 = line_data[7]
    log_len3 = line_data[8]
    log_len4 = line_data[9]
    log_len = [log_len4, log_len3, log_len2, log_len1]
    log_len = ''.join(log_len)
    log_len = int(log_len,16)
    #move the log pointer
    logaddr = (10) + log_len

    if (logaddr > (10)):
        payload = line_data[(10):logaddr]
        payload = ''.join(payload)
        payload = payload.decode("hex")
    else:
        payload = "No Payload"

    #checksum value
    checksum1 = line_data[(logaddr)]
    checksum2 = line_data[(logaddr+1)]
    checksum3 = line_data[(logaddr+2)]
    checksum4 = line_data[(logaddr+3)]
    checksum = [checksum4, checksum3, checksum2, checksum1]
    checksum = ''.join(checksum)
    checksum = int(checksum,16)

    print timestamp,"ns :",log_id," ",module_id,":",payload,"-checksum:",checksum
    print ""
    return

#*********************************************************************************************
#@brief- this function prints out the details of the packet
#
#@param- packet: contents of the log file
#@return- void
#*********************************************************************************************
def packet_print(line_data):  
         first_char = int(line_data[0],16)
         #function to decide whether the payload is a string or item
         if (first_char == 6):        
             logaddr = item_string(line_data)
         elif (first_char < "20"):
             logaddr = item_decode(line_data)
         else:
         #value so the next item can be logged
             print "Not a valid log"

#***************************************************************************************
#@brief- This is the main function definition that will be in charge of the entire flow
#
#@param- void
#@return- void
#*****************************************************************************************
def main():
    with open("host_log_file.txt","rba") as file:
        line = file.readlines()
        n = 0
        while (line):
            element = line[n].split()
            packet_print(element)
            n = n + 1

#************************
#calling the main function
#***********************

main()


#******************************************************************************************
#****************End of File***************************************************************
#******************************************************************************************
