import subprocess
import psutil
import os

class ProcessTimer:
        def __init__(self,command):
          self.command = command
          self.execution_state = False
      
        def execute(self):
          self.max_vms_memory = 0
          self.max_rss_memory = 0
      
          self.t1 = None
          self.t0 = time.time()
          self.p = subprocess.Popen([self.command])
          self.execution_state = True
      
        def poll(self):
          if not self.check_execution_state():
            return False
      
          self.t1 = time.time()
      
          try:
            pp = psutil.Process(self.p.pid)
      
            #obtain a list of the subprocess and all its descendants
            descendants = list(pp.children(recursive=True))
            descendants = descendants + [pp]
      
            rss_memory = 0
            vms_memory = 0
      
            #calculate and sum up the memory of the subprocess and all its descendants 
            for descendant in descendants:
              try:
                mem_info = descendant.memory_info()
      
                rss_memory += mem_info[0]
                vms_memory += mem_info[1]
              except psutil.NoSuchProcess:
                #sometimes a subprocess descendant will have terminated between the time
                # we obtain a list of descendants, and the time we actually poll this
                # descendant's memory usage.
                pass
            self.max_vms_memory = max(self.max_vms_memory,vms_memory)
            self.max_rss_memory = max(self.max_rss_memory,rss_memory)

          except psutil.NoSuchProcess:
            return self.check_execution_state()  
      
        def is_running(self):
          return psutil.pid_exists(self.p.pid) and self.p.poll() == None

        def check_execution_state(self):
          if not self.execution_state:
            return False
          if self.is_running():
            return True
          self.executation_state = False
          self.t1 = time.time()
          return False
      
        def close(self,kill=False):
          try:
            pp = psutil.Process(self.p.pid)
            if kill:
              pp.kill()
            else:
              pp.terminate()
          except psutil.NoSuchProcess:
            pass

CLANG_BIN_PATH = "/usr/bin/clang"
full_path_header = '"/Users/faryab/Documents/UM Academics/Fall 2021 Classes/EECS583/Final Project/583-neuro-vectorizer/tests/header.c"'

filename = "s1_128_sub_0.c"

cmd1 = 'timeout 2s ' +CLANG_BIN_PATH +  ' -O3 -lm '+full_path_header +' ' +filename+' -o ' +filename[:-1]+'o'

cmd2 = filename[:-1]+'o'

print(cmd2)
    
try:
    ptimer = ProcessTimer(cmd2)
    ptimer.execute()
    #poll as often as possible; otherwise the subprocess might 
    # "sneak" in some extra memory usage while you aren't looking
    while ptimer.poll():
        time.sleep(.5)

    runtime = ptimer.max_vms_memory
    print("memory usage: ", runtime)
except:
    runtime = None #None if fails
    logger.warning('Could not compile ' + filename + 
                    ' due to time out. Setting runtime to: ' +
                    str(runtime)+'. Considering increasing the timeout,'+
                    ' which is currently set to 2 seconds.')
finally:
    #make sure that we don't leave the process dangling?
    ptimer.close()

print("done!!!")