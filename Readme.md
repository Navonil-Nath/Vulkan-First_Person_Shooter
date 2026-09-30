//creating the instance
------one --------
setting up the vulkan instance so that it automatically detects the graphics driver and allow our application to communicate with the vulkan graphics drivers
also setting it up such that the instance automaticcaly detects the validation layer extensions then querry the glfw extensions and then set up the debug callback mechanism for putting any gpu error or application error regarding drivers communication,dangling pointers etc to the terminal