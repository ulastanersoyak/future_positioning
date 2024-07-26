#!/usr/bin/env python


class utm:

    def __init__(self, longitude: int, latitude: int):
        self.longitude = longitude
        self.latitude = latitude


class data_package:

    def __init__(self, location: utm, unix_time: int):
        self.location = location 
        self.unix_time = unix_time
