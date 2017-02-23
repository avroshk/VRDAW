"""
# Copyright (C) 2017 Avrosh Kumar (avroshkumar@gmail.com)
#
# 

"""


import LiveOSC

_Framework.ControlSurface import ControlSurface #

class VRDAW(ControlSurface):
    __module__ = __name__
    __doc__ = "Main class that initializes communication between VR application & Ableton Live"

    def __init__(self, c_instance):
        
        ControlSurface.__init__(self, c_instance)

        self._VRDAW__c_instance = c_instance
        self.LiveOSC_Object = LiveOSC.__init__(self, c_instance)



