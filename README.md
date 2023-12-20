MISC
    - citySize constant in sampleCity.cpp can be altered to change the size of the city.
    - How fast a day is can change in the WorldEnvironment timescale variable.
    - press space to stop the sun from rotating if you want to inspect the specular light.
    - since mouse cursor has no boundries, you must use esc to close window
CAMERA
    - w,a,s,d to move forward,left,back,right relative to camera.
    - q,e to move up and down relative to camera.
    - hold shift while moving camera for "walking speed"
    - scroll wheel up and down to change camera velocity

LIGHTING
    - The scene has basic ambient lighting to give it a base amount of light
    - There is directional light from the sun 
    - specular lighting via a specular map.
    - There is 1 shader for the world where different aspects of the lighting can be enabled and disabled

ENVIRONMENT
    - In the environment folder there are necessary files for to set up an observer pattern
    - The WorldEnvironment class is a singleton that different classes in the program can observer
      to get updated information about the world. There is one BasicBuilding and rectangle registered
      to get information that can be set as uniforms in their materials.