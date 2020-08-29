# Aerobot2020

Для корректной работы необходимо установить драйвер для видеокарты
Установить ROS Melodic (http://wiki.ros.org/melodic/Installation/Ubuntu)
Установка и настройка среды ROS (http://wiki.ros.org/ROS/Tutorials/InstallingandConfiguringROSEnvironment)
Рекомендуется установка catkin tools (https://catkin-tools.readthedocs.io/en/latest/installing.html)
Раcпаковать архив симулятора (Firmware,robot_setup_tf) в рабочее пространство ROS (catkin_ws/src)
Зайти в дерикторию Firmware и прописать команду: `make clean`

#### Установка требуемых пакетов:

```bash
sudo apt-get install python-jinja2
sudo pip install numpy toml
```

#### Установка mavros:

```bash
sudo apt-get install ros-melodic-mavros ros-melodic-mavros-extras
```

#### Установка geographiclib:

```bash
wget https://raw.githubusercontent.com/mavlink/mavros/master/mavros/scripts/install_geographiclib_datasets.sh
sudo chmod +x ./install_geographiclib_datasets.sh
sudo ./install_geographiclib_datasets.sh
```
#### Установка репозитория

```bash
git clone git@github.com:KSurov/Aerobot2020.git
cd Aerobot2020/
git submodule update --init
```

#### Компиляция рабочего пространства ROS (catkin_ws)

Запуск происходит из дериктории Firmware
В терминале поочередно прописать:

```bash
DONT_RUN=1 make px4_sitl_default gazebo
source ~/catkin_ws/devel/setup.bash 
source Tools/setup_gazebo.bash $(pwd) $(pwd)/build/px4_sitl_default
export ROS_PACKAGE_PATH=$ROS_PACKAGE_PATH:$(pwd)
export ROS_PACKAGE_PATH=$ROS_PACKAGE_PATH:$(pwd)/Tools/sitl_gazebo
```

Затем перейти в дерикторию **Firmware/launch** 
В терминале выбрать требуемый уровень:

```bash
roslaunch first_world.launch (second_world.launch, third_world.launch)
```

#### Список ROS-топиков:

**/laser/scan** - данные с кругового лидара
**/iris_rplidar/usb_cam/image_raw** - изображение с камеры, направленной вниз
**/r200/depth/image_raw** - изображение со стереокамеры, направленной вперед
**/r200/depth/points** - облако точек со стереокамеры
**/mavros/px4flow/ground_distance** - данные с высотомера
**/mavros/imu/data_raw** - данные с инерциальных датчиков

#### Список ROS-топиков, которыми нельзя пользоваться:

**/mavros/global_position/raw/fix**
**/mavros/global_position/raw/gps_vel**
**/mavros/global_position/raw/satellites**
**/mavros/odometry/in**
**/mavros/altitude**

------

##### Изменения в версии v2:

Отлючен модуль GPS.
При первом запуске для переведения дрона с режима полета по GPS на режим Optical_flow:

```bash
rosrun mavros mavparam set EKF2_AID_MASK 2
```

В модель квадрокоптера добавлен модуль px4_flow.
В первой сцене (first_world) добавлена текстура травы, а также дополнительные объекты вокруг здания.
Размеры QR-кодов над дверными проемами во второй сцене (second_world) приведены к указанным в регламенте.
