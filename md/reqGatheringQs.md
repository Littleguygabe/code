1. What is the primary difference between requirements and specifications
Requirements are general behaviours that the clients needs the system to be able to perform whereas specifications are the decompositions of requirements that show how each requirement is going to be achieved/the process that is going to be used to implement the requirement. 

The specifications are then later used as a testing benchmark because if the system meets all the specifications then inherently it will also meet all the requirements as the specs are decompositions of the requirementes

2. Briefly explain the purpose of a user story in agile development
User stories allow the developers to be able to take a different point of view of the system as it means they have to think about the program in a non-tehcnical pre-specified way which can result in specifications or requirements which were not previously identified being discovered. 

Furthermore they can be used in the testing process to make sure that a given stakeholder can perform a certain activity, and by giving the testers a pre-defined scenario to pretend they are in.

3. List the three main components of a user story sentence structure
- the stake holder
- the goal/the action they want to do
- why they want to perform the action

4. what is one advantage and one disadvantage of using user stories
One advantage is that it allows the developers to take a different view point on the program from a non-technical stand point so that they can make sure its accessable to everyone. 

One disadvantage is that it doesn't allow much representation for non-functional requirements as it can be hard to encapsulate concepts such as system performance into the format of a user test as the user typically wont see the performance side of things unless it is very high level performance features, such as load speed for a page.

5. explain the difference between functional and non-functional requirements 
A functional requirement is a specific behaviour that the system should have, such as the user should be able to see their records, these are typically derived directly from the user needs and/or business processes and are typically critical to the software meeting the requirements. Furthermore functional requirements generally have a pass/fail type of test where the requirement is either met or it isn't.

On the other hand non-function requirements typically describe requirements that are not essential to the running of the system however are still specified as requirements, this includes things such as quality, performance, accessability etc. Generally non-functional requirements are harder to test because they have no hard pass/fail - although this can be implemented by using thresholds they must meet - they typically have a scale at which they can score upon, for example if you were testing the performance of a system you might define a threshold that is acceptable however ultimately the result of the test isn't going to be a hard pass/fail

In summary the functional requirements are effectively 'what' the system needs to be able to do whereas non-functional are 'how well' can the system perform certain behaviours

6. Provide an example of a functional requirement for a system
be able to login to application 

7. Prove an example of a non-functional requirement related to performance or security
The system must have a load time of <2s with 1000 concurrent users for >90% of users

8. What is the primary benefit of using interviews or focus groups for requirements investigation compared to surveys
Interview or focus groups can allow you to collect a lot more detailed information about the requirements of the system in a shorter period of time as everyone has the ability to say exactly what they need out of the system rather than having to answer pre-defined questions about their requirements which inherently limits the range of requirements that can be specified.

9. why are observations a valuable technique for gathering requirements, even if stakeholders provide information
Observations are a valuable technique because some actions taken by stakeholders may be sub-concious in which case they aren't going to specify that they may need to be able to do a certain behaviour within the system. Furthermore observations are key for when using methods like tech tours as we need to be able to see how the new system being developed should be able to integrate into the environment/workflow the software is being used in, so making sure the system is cohesive with the current setup for the client is key to ensuring the software is used effectively.

10. What is a technology tour and what does it aim to discover
a technology tour is when the software engineering business looks around the client's current working environment to be able to pickup on how the system should implement into the real-world setting that it is going to be used in. These are important as sometimes the client may miss out key features that the system may need to integrate with so by being able to physically see the workspace and observe how it is used it can give the developers a better understanding of the optimal way to implement the system in to the current working environment