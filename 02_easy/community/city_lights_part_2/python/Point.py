class Point:


    def __init__(self, x=0, y=0, z=0, brightness=0):
        self.__x            = x
        self.__y            = y
        self.__z            = z
        self.__brightness   = brightness
    
    def get_x(self):
        return self.__x

    def get_y(self):
        return self.__y

    def get_z(self):
        return self.__z

    def get_brightness(self):
        return self.__brightness
    
    def add_brightness(self, brightness):
        self.__brightness += brightness

        if self.__brightness > 35:
            self.__brightness = 35
    
    def __str__(self):
        return f"({self.__x, self.__y, self.__z} : {self.__brightness})"
