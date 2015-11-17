libdynamixel
============
libdynamixel is a C++ interface to the `dynamixel <http://en.robotis.com/index/product.php?cate_code=101010>`_ actuators. Currently, we have library code and a utility that uses it to offer a few functionalities like changing the IDs, the control mode (wheel or joint) and the baudrate.

This library is used as the main building block for a ROS node that can be found in the `dynamixel_control <https://github.com/jbmouret/dynamixel_control>`_ repository. It is also used for an `hexapod controller <https://github.com/resibots/hexa_control.git>`_ we use for our experiments as part of the `ResiBots project <http://www.resibots.eu/>`_.

Features
========
- both Dynamixels of the AX and MX series are supported (despite the names in the source code)
- support for all instructions and messages of the version 1.0 of the Dynamixel communication protocol
- full C++ api

Building
========
Dependencies :

- python2.x
- g++
- Boost C++

The build system for libdynamixel is Waf, which only dependency is python.

.. highlight:: shell

Then, configure and build the programm::

    python2.x waf configure
    python2.x waf

where `x` is to be replaced by the actual version number of your python. That's it ! You get the ``dynamixel`` toolset and the demo programms compiled in the ``build/default/src`` folder.

For now, the demo programs are not at a working stage and should not be used. Conversely, ``dynamixel`` is a working program that we use regularly, even though its command line interface needs some polishing.

Further documentation
=====================
The documentation for libdynamixel is being written and should be published soon.

Support
=======
This library is actively used and regularly developped. If you need some help, feel free to `fill an issue <https://github.com/resibots/libdynamixel/issues/new>`_ on this repository. We'll do our best to be responsive.

Alternative software
====================

Inria FLOWERS team developped `pybot <http://poppy-project.github.io/poppy-docs/pypot/doc/index.html>`_, a python library to control a Dynamixel-based robot.

Please let us know if you developped an other library for Dynamixels.

License and authors
===================
This work is distributed under the terms of the `CeCILL-C <http://www.cecill.info/licences.en.html>`_ license. © UPMC and INRIA.

The authors for this library are Jean-Baptiste Mouret, Antoine Cully and Dorian Goepp.