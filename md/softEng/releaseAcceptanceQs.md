1. What is the primary objective of release testing
Release testing is making sure that the system has met all the specifications that were defined after looking at the requirements for the system. This is the last phase of testing done before the program is passed onto the client for acceptance testing

2. How does release testing differ from integration testing
Release testing is about looking at a program as a whole to make sure that all aspects of the specification have been met, this type of testing is the last level of testing done before the program is put infront of the client to be have acceptance testing performed. However integration testing on the other hand is aimed at testing small sections of the program in isolation - typically a few functions/classes - that communicate with one another to test that the classes can correctly communicate with one another, this is the first level of testing where multiple sections of the program are being ran together however it is not the whole program - like in release testing.

4. Name and briefly describe three strategies for release testing
- performance driven testing, this is where the system is essentially stress tested to make sure that it can perform up to a certain standard whilst in certain conditions. Ie test the system as a <2s load time with 1000 concurrent users 90% of the time
- high-level specification driven testing, this is testing where we use the high level interface of the finished program to test that the system meets the specification in every day use not just when we are performing targetted tests through code
- scenario driven tests, this is when we take a scenario created during the requirements gathering phase and then derive tests based on the scenario to try and simulate normal use on the system to make sure it still runs well for a range of scenarios and users

5. Who typically performs acceptance testing
Usually the software engineering company will take the system to the client to setup the acceptance tests so the client can see the software implemented on their system using their data and then the testing is performed by the client or the client represtative.

6. What is the main goal of acceptance testing from the clients perspective
From the client's perspective acceptance testing is there to ensure that the software that has been produced matches the requirements they set at the start of the development process to a suitable degree - there may be some errors - and then once testing is complete and they have seen how the system performs it is then up to them to decide whether the system was adequate and whether to accept or reject it. if they do reject it it is then a matter of deciding what would make it acceptable from where it currently is.

7. Why is it important to define acceptance criteria early on in the development process
It is important because we can see from the development cost pyramid that by the time the development process starts approaching a release version/acceptance testing the cost to make changes increases exponentially. Therefore having to make changes later on in the development cycle is worse for everyone, therefore by having the accpetance criteria defined early on in the process allows both parties to be exactly clear on what is required from the system and in the long run will save time and money as the program won't have to have sections of it re-built.

8. What are the key steps in the acceptance testing process

- define acceptance criteria -> define the criteria for the software to be acceptable (should ideally be done before any programming has been done - normally when the contract is signed)
- plan acceptance testing -> set up the computers and any data that you are going to need for the tests and plan what tests are going to be performed
- derive the acceptance tests -> actually coding the tests
- run acceptance tests 
- negotiate results -> looking at the results of the tests and negotiating whether they meet the creiteria or not and if not how far off are they? are they still acceptable etc
- accept or reject the system

9. What is user testing and how is it different from acceptance testing
User testing is when the system is released to a select number of users to be tested with real world use from real world users, this generally comes in 2 forms:
- Alpha testing, this is the first level of user testing when a select amount of users get to tests a system that has only just been released, as a result there may be a larger number of bugs and issues within the program
- Beta testing, this is the next level up from alpha testing and is generally a system that is closer to being release ready and therefore it is provided to a larger number of users to get real world testing done, however just because it is closer to being release ready doesnt mean it is bug free.

This differs from acceptance testing because this is being done by real world users that have no stake in the software and are solely there to ensure that the system holds up under real world use whereas acceptance testing is just aimed to show that the software produced does in fact meet all of the requirements that were initially set by the client.

10. Explain the difference between alpha testing and beta testing
Alpha testing is when the program has only just been loosely finished and may still have a large number of bugs and issues, as a result it is only released to a select number of users for real-world testing as there is no guaruntee that it is stable

Beta testing on the other hand is still using a pre-release system however it is going to be closer to being release ready and therefore has more users that are running the pre-release version, the beta is generally opened up to the public through beta test programs in which the user gets to pre-release software and in return the essentially perform real use tests and are just asked to report any bugs they run into during use