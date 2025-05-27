1. What is the primary difference in the knowledge base structure between an expert system and a case-based reasoning system

An expert system is a knowledge base built on top of knowledge collected from experts in certain fields, however this knowledge can typically be subjective and therefore different aspects of data within the base may contradict one another. Case-based reasoning on the other hand looks at the objective facts of a case and then build its logic and reasoning on top of that so that it generates responses based on evidence rather than subjective opinion.

**should have emphasised for expert-knowledge systems the knowledge is typically represented as a set of rules that is if-then along with sets of heuristics. Then for case based reasoning clarify that the knowledge base is a collection of past cases, each describing a problem, its solution and the outcome. The system then reasons by finding similar past cases to solve new problems (somewhat like apttern matching)

2. Why was domain knowledge considered dominant in ai methods until the '90s

domain knowledge was considered dominant as it provided accurate, specific knowledge based on a given subject so allowed for more informed answers than just background or general knowledge. Further more if building systems such as top down decision trees domain knowledge would allow for better rules to be formulated and therefore provide more accurate outputs for a given input

3. What is the bottleneck in building a knowledge based system

the bottleneck within the acquisition/engineering section of building a knowledge base is that fact that human knowledge is typically incredibly unstructured and often complex, further more expert knowledge is often opinionated/subjective making it harder to produce a knowledge base without contradictions that provides objective results. So in summary the bottleneck comes from trying to get human knowledge into an objective understandable format to be processed

4. besides the potential ambiguity and lack of uniformity what is a key problem in using natural language to represent logic in a KBS?

Another key problem is how we enable the system to be able to reason with the given knowledge as a natural language, ie how we encapsulate the knowledge in a way that allows a computer to be able to analyse it and draw conclusions based on the knowledge stored

5. in the context of knowledge based systems, what is the purpose of the representation phase?

The purpose of the representation phase is to put the stored knowledge into a standaradised format (conjunctive normal form) so that the system can then analyse the knowledge it already has and hence draw new logical conclusions from it.

6. Briefly explain the concept of unification in the resolution rule inference method

The concept of unification is how we can link 2 logical predicates (clauses) together to create a new logical links bewteen knowledge that already exists.

7. What is the requirement for a knowledge base to be used with the resolution rule method

That the KBS is in conjuctive normal form

8. If the resolution rule process results in an empty clause, what does this signify about the negated statement added to the knowledge base

That a contradiction has occured hence the negated statement is proven to be not true (original statement was true)

9. Give and example of a logical connective used in predicate logic and explain its meaning

One example of a logical connective is (for) all, this implies that the condition holds true for all variables of a given predicate

10. What are the three main steps inolved in applying knowledge, or reasoning within a KBS

Acquisition - getting the knowledge off of experts or cases
Representation - ensuring that data is represented in the correct format to be reasoned with in the database
Reasoning - Reasoning with the knowledge in the KBS to produce a coherent and logical output