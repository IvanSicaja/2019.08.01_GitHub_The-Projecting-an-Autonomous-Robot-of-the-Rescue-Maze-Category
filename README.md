🧾 🎯 **Project Title:** **THE PROJECTING AN AUTONOMOUS ROBOT OF THE RESCUE MAZE CATEGORY**  
📅 **Project Timeline:** **August 2019 – October 2021**  
🎥 YouTube Demo: [Link: https://youtu.be/3sTD7d_HzC4](https://youtu.be/3sTD7d_HzC4)  
📦 GitHub Source Code: <https://github.com/IvanSicaja/2019.08.01_GitHub_The-Projecting-an-Autonomous-Robot-of-the-Rescue-Maze-Category>  
\----------------------------------------------------------------------------------------------------------------

🏷️ My Personal Profiles: ⬇︎  
🎥 Video Portfolio: To be added  
📦 GitHub Profile: <https://github.com/IvanSicaja>  
🔗 LinkedIn: <https://www.linkedin.com/in/ivan-si%C4%8Daja-832682222>  
🎥 YouTube: <https://www.youtube.com/@ivan_sicaja>  
\----------------------------------------------------------------------------------------------------------------

### 📚🔍 Project description: ⬇︎⬇︎⬇︎

### 💡 App Purpose

To design a **rescue maze mobile robot** with autonomous **navigation, victim detection, and package delivery**, capable of operating in **unpredictable rescue environments** with robust AI-driven perception.

**Key Robot Capabilities:**

- **Autonomous character recognition (OCR)**
- **Autonomous color recognition**
- **Partially autonomous drive in the maze** (need a lot of testing and calibration for fully autonomous drive and labyrinth mapping)
- **Thermal victim recognition**
- **Package delivery**
- **Ability to master a climb of 25 degrees** (all-wheel drive, strong grip)
- **Independent axle maneuvering**
- **Remembering positions (encoders)**...

**🧠 How It Works**  
The project is very complex and demands knowledge in different areas (**3D modeling, 3D printing, advanced programming skills in different languages, researching ability, expert knowledge of every electrical component working principles, image processing, cause-and-effect analysis...**)  
The brains of the robot are **microcontroller Teensy 3.5** and **Raspberry Pi 4B**.

The robot is also equipped with:

- **2x optical camera**
- **2x thermal camera**
- **6x IR lidar sensor**
- **1x color sensor**... (more can be found at GitHub in my publication paper: _The projecting an autonomous robot of the rescue maze category.pdf_ -> Caption 4.3)

**Optical character recognition:**  
In this project, we trained a **Convolutional Neural Network (CNN)** on an image examples with the Python module **TensorFlow**. Images are converted into **.CSV file** because of speeder processing. The input image is filtered with different filters (**Grayscale, Gaussian Blur, Threshold, Binary, Dilatation**) in order to speed up image processing (replace three color channels with one channel, **RGB -> grayscale**). Reduce noises (the dust on the live video capturing). Getting smooth and sharp character edges is the most important characteristic for successful character recognition. The trained model accuracy is **77.54%** which is a target because we want to get high reliability and avoid CNN overfitting.

**Object detection:**  
Developed the custom script with the Python computer vision module **OpenCV** which filters the character that should be recognized from the other objects in the robot's surroundings. The script works on the principle of **character height and proportion**, together with the **dynamic noise filtering**.

**Maze mapping:**  
Maze mapping is done in my Python module **Turtle**. Every maze field is properly recognized by the robot's **distance and color sensors**. After all maze fields are mapped, they are sent to the backend and the shortest path is calculated by the artificial intelligence searching algorithms such as: _Breadth-First Search, Depth-First Search, A Algorithm_\*...

**Hardware choosing and connecting:**  
The entire process of choosing **hardware platforms, supported protocols, and hardware capabilities** is done. E.g. the **video camera** must have a corresponding **focal length** otherwise it will be useless, **framerate, resolution, additional light source**, **motors** should have expected speed, **distance sensors** should be precise and able to work in a maze, **robot brain** should be able to do high computation payload and support Python…

**Frame design and 3D printing:**  
Entire robot is **3D designed** with **Fusion 360 CAD/CAM** software and **3D printed** with the **Ultimaker 3+** 3D printer with corresponding **filament, density**, etc.

**Developing mechatronic code:**  
**Arduino** is used to control all **sensors and actuators** on the robot except the **camera** which is controlled by **Raspberry Pi 4B** computer.

### ⚠️ Note

Achieving fully **autonomous drive** and **labyrinth mapping** requires extensive testing and calibration.  
I would especially like to thank **Mirko Pezo** and **Stjepan Mikulic** for their exceptional contribution to the development of this project .

### 🔧 Tech Stack

**Python, Convolutional Neural Network (CNN), OpenCV – Computer Vision, Pandas, TensorFlow, Keras, scikit-learn, Git, Linux, Fusion 360, 3D design, 3D printing, Arduino, Raspberry Pi, Teensy, Visual Studio Code, Turtle (Python), AI Search Algorithms (BFS, DFS, A\*)**

---

### 📸 Project Snapshot

<p align="center">
  <img src="https://github.com/IvanSicaja/2019.08.01_GitHub_The-Projecting-an-Autonomous-Robot-of-the-Rescue-Maze-Category/blob/main/0.1_GitHub/1.0_Description_4_media_key_messages_%26_captions/2.0_Thumbnail_1.png?raw=true" 
       alt="Rescue Maze Robot Preview 1" 
       width="640" 
       height="360">
</p>

<p align="center">
  <img src="https://github.com/IvanSicaja/2019.08.01_GitHub_The-Projecting-an-Autonomous-Robot-of-the-Rescue-Maze-Category/blob/main/0.1_GitHub/1.0_Description_4_media_key_messages_%26_captions/2.0_Thumbnail_2.png?raw=true" 
       alt="Rescue Maze Robot Preview 2" 
       width="640" 
       height="360">
</p>

<p align="center">
  <img src="https://github.com/IvanSicaja/2019.08.01_GitHub_The-Projecting-an-Autonomous-Robot-of-the-Rescue-Maze-Category/blob/main/0.1_GitHub/1.0_Description_4_media_key_messages_%26_captions/2.0_Thumbnail_3.png?raw=true" 
       alt="Rescue Maze Robot Preview 3" 
       width="640" 
       height="360">
</p>

<p align="center">
  <img src="https://github.com/IvanSicaja/2019.08.01_GitHub_The-Projecting-an-Autonomous-Robot-of-the-Rescue-Maze-Category/blob/main/0.1_GitHub/1.0_Description_4_media_key_messages_%26_captions/2.0_Thumbnail_4.png?raw=true" 
       alt="Rescue Maze Robot Preview 4" 
       width="640" 
       height="360">
</p>

<p align="center">
  <img src="https://github.com/IvanSicaja/2019.08.01_GitHub_The-Projecting-an-Autonomous-Robot-of-the-Rescue-Maze-Category/blob/main/0.1_GitHub/1.0_Description_4_media_key_messages_%26_captions/2.0_Thumbnail_5.png?raw=true" 
       alt="Rescue Maze Robot Preview 5" 
       width="640" 
       height="360">
</p>

<p align="center">
  <img src="https://github.com/IvanSicaja/2019.08.01_GitHub_The-Projecting-an-Autonomous-Robot-of-the-Rescue-Maze-Category/blob/main/0.1_GitHub/1.0_Description_4_media_key_messages_%26_captions/2.0_Thumbnail_6.png?raw=true" 
       alt="Rescue Maze Robot Preview 6" 
       width="640" 
       height="360">
</p>

---

### 🎥 Video Demonstration

<p align="center">
  <a href="https://youtu.be/3sTD7d_HzC4">
    <img src="https://img.youtube.com/vi/3sTD7d_HzC4/0.jpg" 
         alt="Watch the demo" 
         width="640" 
         height="360">
  </a>
</p>

---

### 📣 Hashtags Section

**\# #AutonomousRobotics #RescueMaze #RoboticsEngineering #AI #ComputerVision #OCR #ObjectDetection #PathPlanning #CNN #TensorFlow #OpenCV #EmbeddedSystems #RaspberryPi #Arduino #3DPrinting #Fusion360 #Mechatronics #AutonomousNavigation #MachineLearning**
