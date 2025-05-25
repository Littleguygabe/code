1. Define Release Management
Release Management is the methodically controlled release of new software versions in an organised and structured manner

2. what is build/configuration management used for
Build/config management is used for when a system is ready to be released and the company that produced the software wants to release it onto multiple different platforms, a build configuration then allows us to create a build file for a given system implementation that acts as a blueprint for the build and then a builder can understand this script and will provide all the extra dependencies needed for the system to be able to run on the given operating system. This can therefore allow us to quickly be able to create builds for lots of different platforms, or we can create standardised build scripts so whenever a new prototype of the system is produced (for example if using eXtreme Porgramming) then it can automatically be built after tests and then released very quickly (like chromium canary builds)

3. Explain the importance of version control in a software development workflow 
Allows developers to track changes to the code as they are commited and therefore it can also allow us to revert to old versions of the code if we need to go back to before a bug existed or create a new feature based on an old version. This also allows us to create branches of code which means that a company can continue to work on an old version of the program/continue support seperate of the newest version that has been released, for example how microsoft continued support for windows 10 long after windows 11 was released

4. Describe the concept of continuous integration
Continuous integration is the idea that code changes are being constantly added to the current working version, so when someone pushes their code to the database/repository then automatic tests are ran on their code to make sure it meets a certain standard of useability and then if all tests are passed then their code is created as a release version of the software. This means changes are being constantly made however the changes are safe to some degree as they have automatic tests to pass.

In addtion continuous integration aims to identify integration errors early, which therefore can help reduce costs as we handle these issues sooner in the development life-cycle, which we can see from the cost pyramid will drastically reduce costs.

5. List 2 benefits of continuous integration
- Allows constant agile development of the system
- Ensures that all release versions pass a certain level of standardised testing

6. What information is typically included in a build version
Typically a build configuration will store information about the dependencies for the OS that the system is being deployed upon, or components that may be needed by the system such as libraries. Furthermore it can store metadata, version numbers, etc.


7. Briefly explain automatic deployment
Automatic deployment is the idea that as soon as a new version is created and passes certain automatic tests the system will then apply a build configuration to it and therefore create a new release version of the software. This then pushes the release to the target environment once an acceptable build has been created 