from __future__ import with_statement #compatibility for Live 9, need to be written at the first line of the script
import Live #you import Live, in order to be able to use its components

import random
import time
import sys
import threading
import Queue
import datetime

import rtmidi_python as rtmidi

#Transport.py 
#This is a stripped-down script, which uses the Framework classes to assign MIDI notes to play, stop and record.
from _Framework.ControlSurface import ControlSurface # Central base class for scripts based on the new Framework
from _Framework.TransportComponent import TransportComponent # Class encapsulating all functions in Live's transport section
from _Framework.SessionComponent import SessionComponent # Class encapsulating all functions in Live's transport section
from _Framework.ButtonElement import ButtonElement # Class representing a button a the controller

import OSC

# from SpecialTransportComponent import SpecialTransportComponent
# from MIDI_Map import *

class Transport(ControlSurface):

    # count = 0
    __module__ = __name__
    __doc__ = "VR DAW Test"

    # def setLock(self, addr, tags, data, client_address): 
    #     self.log_message("DATA DATA DATA: " + str(data))
    #     if data == 0:
    #         self.isLocked = False
    #         self.my_serve_forever()
    #     else:
    #         self.isLocked = True

    def playGlobal(self, addr, tags, data, client_address):
        # self.isLocked = True
        text_file = open("/Users/avrosh/Desktop/Output.txt", "a+")
        txt = str(datetime.datetime.utcnow()) + "-> OSCMessage '%s' '%s' from %s: " % (addr, tags, client_address)
        txt += str(data)
        text_file.write(txt+"\n")
        # self.log_message('PLAY')
        self.my_song.start_playing()
        # print()
        text_file.close()
        # self.isLocked = False
        # self.my_serve_forever() 

    def stopGlobal(self, addr, tags, data, client_address):
        # self.isLocked = True
        text_file = open("/Users/avrosh/Desktop/Output.txt", "a+")
        txt = str(datetime.datetime.utcnow()) + "-> OSCMessage '%s' '%s' from %s: " % (addr, tags, client_address)
        txt += str(data)
        text_file.write(txt+"\n")
        # self.log_message('STOP')
        self.my_song.stop_playing()
        # print()
        text_file.close()
        # self.isLocked = False
        # self.my_serve_forever() 


    def panTrack(self, addr, tags, data, client_address):
        # self.isLocked = True
        # self.my_song.start_playing()
        text_file = open("/Users/avrosh/Desktop/Output.txt", "a+")
        txt = str(datetime.datetime.utcnow()) + "-> OSCMessage '%s' '%s' from %s: " % (addr, tags, client_address)
        txt += str(data)
        text_file.write(txt+"\n")
        # text_file.write(str(self)+"\n")
        # text_file.write(str(self.default_port)+"\n")


        self.log_message("---------------------------------------------")
        self.log_message(txt)
        self.log_message(str(self))


        text_file.close()  
        # self.isLocked = False
        # self.my_serve_forever()  

    def __init__(self, c_instance):
       
        ControlSurface.__init__(self, c_instance)

        #don't know the use of this, but it is required in live 9 scripts
        with self.component_guard():               
            self.__c_instance = c_instance  
            self.isLocked = False

         
           
            # transport = TransportComponent() #Instantiate a Transport Component
            # transport.set_play_button(ButtonElement(True, 0, 0, 61)) #ButtonElement(is_momentary, msg_type, channel, identifier)
            # transport.set_stop_button(ButtonElement(True, 0, 0, 63))
            # transport.set_record_button(ButtonElement(True, 0, 0, 66))

            # Here is some Live API stuff just for fun """
            app = Live.Application.get_application() # get a handle to the App
            maj = app.get_major_version() # get the major version from the App
            mini = app.get_minor_version() # get the minor version from the App
            bug = app.get_bugfix_version() # get the bugfix version from the App


            self.log_message('In the beginning....')
            self.log_message(str(self))
            # midi_out = rtmidi.MidiOut()
            # midi_out.open_virtual_port("VRDAW_Midi")
            # for port_name in midi_out.ports:
            #      self.log_message(port_name)
            # midi_out.open_virtual_port("VRDAW_Midi")

            # song_beats = Live.Song.bars

            # song_beats.fget(Live.Song.BeatTime)
            # self.log_message(song_beats)

            

            # self.log_message(dir(Live.Song.Song))
            # self.log_message(dir(Live.Song.TimeFormat))

            # my_song = Live.Song.Song.get_data(app)
            # my_song = Live.Song.__init__() 
            # my_song = Live.Song.__init__("VRSONG")
            # the_song = my_song.Song
            # self.log_message(my_song.__dict__)
            # self.log_message(dir(Live.Application))

            self.my_song = Live.Application.get_application().get_document()  

            # self.my_song.start_playing()
            # self.my_song.stop_playing()

            self.default_port = 9999
            addr = '127.0.0.1'

            listen_address = (addr, self.default_port)
            shout_address = (addr, 9001)
            
            self.oscSender = OSC.OSCClient()
            self.log_message("Instantiating OSCClient:")
            self.oscSender.connect(shout_address)   
           
            self.log_message("Instantiating OSCServer:")
            self.oscReceiver = OSC.OSCServer(listen_address) #, self.oscSender, return_port=listen_address[1])
           
            #handlers
            # self.oscReceiver.addDefaultHandlers()
            self.oscReceiver.addMsgHandler('/pan/track0', self.panTrack)     # call handler() for OSC messages received with the /startup address
            self.oscReceiver.addMsgHandler('/transport/play', self.playGlobal)  
            self.oscReceiver.addMsgHandler('/transport/stop', self.stopGlobal) 
            # self.oscReceiver.addMsgHandler('/ableton/free', self.setLock) 
            #Starting OSC server
            self.log_message('Starting OSCServer')

            # addr, tags, data, client_address
            # myargs = ('111.1.1.1','i','0.0', 12345)
            # testThread = threading.Thread(target=self.panTrack, args=myargs)
            # testThread2 = threading.Thread(target=self.panTrack, args=myargs)
            # testThread.start()
            # time.sleep(10)
            # testThread2.start()
            # testThread.join()
            # oscReceiverThread = threading.Thread(target=self.oscReceiver.serve_forever)
            # oscReceiverThread.start()
            # oscReceiverThread.join()

            # while oscReceiverThread.isAlive():
            #     time.sleep(10)
 
            # self.oscReceiverThread = threading.Thread(target=self.oscReceiver.serve_forever)
            # self.oscHandlerThread = threading.Thread(self.panTrack)
            # self.oscReceiverThread.start()
            # self.oscHandlerThread.start()

            # waitbundle = OSCBundle("/pan/track0")
            # waitbundle.setTimeTag(time.time() + 1)

           
            # self.oscReceiverThread = threading.Thread(target=self.oscReceiver.serve_forever)
            # self.oscReceiverThread.start()
            # self.my_serve_forever(self.oscReceiver)

            # self.oscReceiver.serve_forever()

            # self.isLocked = False




           

            # self.oscReceiver.close()

            my_song_time_listener = self.my_song.add_current_song_time_listener(self.my_song_time)

            # my_song_time_listener = threading.Thread(target=self.my_song.add_current_song_time_listener,args=self.my_song_time)
            # my_song_time_listener.start()
            # self.log_message("---------------------------------------------")
            # self.log_message(dir(app))
            # self.log_message("---------------------------------------------")
            # self.log_message(vars(app))
            # self.log_message("---------------------------------------------")
            # self.log_message(dir(Live.Sample))
            # self.log_message("---------------------------------------------")
            # self.log_message(my_song_listener)
            self.log_message("---------------------------------------------")
            # self.log_message(dir(self.panTrack()))
            self.log_message("---------------------------------------------")
            # self.log_message(Live.Song.BeatTime.beats.fget(4))
            # self.log_message(dir(my_song))


            
            self.show_message(str(maj) + "." + str(mini) + "." + str(bug)) #put them together and use the ControlSurface show_message method to output version info to console
            self.log_message('In the end....')
            self.log_message(str(self))
            # self.update_display()

            # threading.Timer(100, self.my_serve_forever).start()

            # self.my_serve_forever()
        #Writes message into Live's main log file. This is a ControlSurface method.
        # self.show_message(time.strftime("%d.%m.%Y %H:%M:%S", time.localtime()) + " : " + __name__) 
        # self.log_message(time.strftime("%d.%m.%Y %H:%M:%S", time.localtime()) + " : " + __name__) 

        # self._setup_transport_control()

        # self.show_message(time.strftime("%d.%m.%Y %H:%M:%S", time.localtime()) + " : HULLLO ULO" + __name__) 
        self.log_message(time.strftime("%d.%m.%Y %H:%M:%S", time.localtime()) + " :  HULLLO ULO" + __name__) 
    
    # def playGlobal(self):
    #     self.log_message('PLAY')
        # self.my_song.start_playing()

    

    # def panTrack(path, tags, args, source):
    #     # which user will be determined by path:
    #     # we just throw away all slashes and join together what's left
    #     # user = ''.join(path.split("/"))
    #     # tags will contain 'fff'
    #     # args is a OSCMessage with data
    #     # source is where the message came from (in case you need to reply)
    #     # print ("Now do something with", user,args[2],args[0],1-args[1]) 
    #     text_file = open("/Users/avrosh/Desktop/Output.txt", "w")
    #     text_file.write(user)
    #     text_file.close()

    # def panTrack(self):
        
    #     self.log_message('TRA LA LA ');
    #     # text_file = open("/Users/avrosh/Desktop/Output.txt", "w")
    #     # text_file.write('data data data')
    #     # text_file.close()

    #  
    
    def update_display(self):
        # super(Transport, self).update_display()
        with self.component_guard():
            # now call your OSC receive function
            self.log_message(str(datetime.datetime.utcnow()) +': Howdy! from update_display')
            self.oscReceiver.handle_request()


    def my_serve_forever(self):
        # self.log_message('That\'s not my name!')
        # self.oscReceiver.serve_forever();

        # while not self.isLocked:
        self.oscReceiver.handle_request()  
      

    def my_song_time(self):
        time_in_beats = self.my_song.get_current_beats_song_time()
        song_time = self.my_song.current_song_time

        oscmsg = OSC.OSCMessage()
        oscmsg.setAddress("/transport/beats")
        oscmsg.append(str(time_in_beats))
        self.oscSender.send(oscmsg)

        oscmsg = OSC.OSCMessage()
        oscmsg.setAddress("/transport/time")
        oscmsg.append(song_time/2)
        self.oscSender.send(oscmsg)

        self.log_message('Beats: '+str(time_in_beats))
        self.log_message('Time: '+str(song_time/2))




        # with open('/Users/avrosh/Desktop/out.txt', 'w+') as f:
        #     # Note that f has now been truncated to 0 bytes, so you'll only
        #     # be able to read data that you wrote earlier...
        #     f.write('somedata\n')
            
            



        # Writes message into Live's main log file. This is a ControlSurface method.
        # self.show_message(time.strftime("%d.%m.%Y %H:%M:%S", time.localtime()) + " : " + __name__) 
        # self.log_message(time.strftime("%d.%m.%Y %H:%M:%S", time.localtime()) + " : " + __name__) 
    
    # def getSong():
    #     """Gets a the current Song instance"""
    #     return Live.Application.get_application().get_document()  

     # def print_volume_handler(unused_addr, args, volume):
     #    print("[{0}] ~ {1}".format(args[0], volume))  
     # SETUP TRANSPORT CONTROL
#     def _setup_transport_control(self):
#         self.transport = SpecialTransportComponent()
#         self.transport.set_metronome_button(self.led_button(PAD_CHANNEL, METRONOME, 127))# Metronome Button
#         self.transport.set_play_button(self.led_button(PAD_CHANNEL, PLAY, 127))#Play Button
#         self.transport.set_stop_button(self.led_button(PAD_CHANNEL, STOP, 127))#Stop Button
#         self.transport.set_record_button(self.led_button(PAD_CHANNEL, REC,127))#Record Button
#         self.transport.set_overdub_button(self.led_button(PAD_CHANNEL, OVERDUB, 127))# Overdub Button
#         self.transport.set_tempo_buttons(self.led_button(PAD_CHANNEL, TEMPO_UP, 127), self.led_button(PAD_CHANNEL, TEMPO_DOWN, 127))
# #       self.transport.set_loop_button(self.led_button(PAD_CHANNEL, LOOP, 127))# Loop Button
#       self.transport.set_tap_tempo_button(self.led_button(PAD_CHANNEL, TAP_TEMPO, 127))#Tap Tempo
       

    # def disconnect(self): #this function is automatically called by live when the program is closed
    #     """clean things up on disconnect"""
    #     self.log_message(time.strftime("%d.%m.%Y %H:%M:%S", time.localtime()) + ": Unloading") #Create entry in log file
    #     ControlSurface.disconnect(self)
    # #     return None