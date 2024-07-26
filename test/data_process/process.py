#!/usr/bin/env python


from data_package import data_package as package 


if __name__ == "__main__":
    with open("/home/ubuntu/gps_location_estimator/test/data/data.txt", "r") as file:
            for line in file:
                  header, _, data = line.partition("$")[2].partition(",")
                  previous_package = package(0,0,0)
                  if header == "GNRMC":
                    sections = data.split(",")
                    time = sections[0]
                    latitude = sections[2]
                    longitude = sections[4]

                    utm_zone = ((longitude + 180) / 6) + 1

                    
                    #        unix time               Y axis                  X axis
                    print(f"time := {time}  | latitude := {latitude} | longitude := {longitude}")