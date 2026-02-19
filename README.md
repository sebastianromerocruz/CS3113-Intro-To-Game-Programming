<h1 align=center>CS-UY 3113 <em>Introduction to Game Programming</em></h1>

<h2 align=center>New York University Tandon School of Engineering</h2>

<p align=center>
    <a href="https://www.learncpp.com/"><img src="https://img.shields.io/badge/Language-C%2B%2B-yellow"></img></a>
    <a href="https://code.visualstudio.com/"><img src="https://img.shields.io/badge/IDE-Visual%20Studio%20Code-blue"></img></a>
    <a href="https://www.opengl.org/"><img src="https://img.shields.io/badge/Library-raylib-white"></img></a>
</p>

---

### _Sections_

1.  [**Lecture Notes**](#1)
2.  [**Instructor and Course Assistant**](#2)
3.  [**Class Information**](#3)
4.  [**Description**](#4)
5.  [**Objectives**](#5)
6.  [**Computer/Software Requirements**](#6)
7.  [**Grading Scheme**](#7)
8.  [**Deadlines, Extensions, and Late Work Policy**](#8)
    - [**Project Schedule**](#8-1)
9. [**Getting Help and Slack**](#9)
10. [**Moses Center Statement of Disability**](#10)
11. [**Academic Integrity**](#11)
    - [**Generative AI**](#11-1)
    - [**Penalties**](#11-2)

---

<a id="1"></a>

### _Lecture Notes_

1. [**The Basics: _Hello, Raylib!_**](lectures/01-introduction)
2. [**Transformations**](lectures/02-transformations)
3. [**Textures / Delta Time**](lectures/03-textures-delta-time)
4. [**User Input / Collision Detection**](lectures/04-user-input-collisions)
5. [**Animation / The `Entity` Class**](lectures/05-animation-entities)

<!--
6. [**Physics**](lectures/06-physics)
7. [**AI In Games**](lectures/07-ai)
8. [**Maps**](lectures/08-maps)
9. [**Scenes**](lectures/09-scenes)
10. [**Effects / Shaders**](lectures/10-effects-shaders)
11. [**Playtesting**](lectures/11-playtesting) -->

<sub>Released on each Friday day before class.</sub>

<br>

<a id="2"></a>

### _Instructor and Course Assistant_

- [**Sebastián Romero Cruz**](https://github.com/sebastianromerocruz)  _(They / Them)_

    | **E-Mail**                                  | **Office Hours**                                                                                                     |
    |---------------------------------------------|----------------------------------------------------------------------------------------------------------------------|
    | [**sebastian.romerocruz@nyu.edu**](mailto:src402@nyu.edu) | [**calendly**](https://calendly.com/profromerocruz) |

- **Eric Zhao (Course Assistant)**

    | **E-Mail**                                  | **Office Hours**                                                     | **Location** |
    |---------------------------------------------|----------------------------------------------------------------------|--------------|
    | [**ez2346@nyu.edu**](mailto:ez2346@nyu.edu) | **Tuesday:** 9:00 AM - 12:00 PM ([ZOOM](https://nyu.zoom.us/j/94279433694)) <br> **Tuesday:** 6:00 PM - 9:00 PM (In Office) <br> **Friday:** 12:00 AM - 2:00 PM (In Office) | Jacobs Hall 223, Room F |

    *If you need to email Eric for anything related to this class, please include the course number (CS3113) and your first and last name in the subject line.*


<br>

<a id="3"></a>

### _Class Information_

- **Pre-Requisites**: [_**CS-UY 2124 Object-Oriented Programming (dē factō)**_](http://bulletin.engineering.nyu.edu/preview_course_nopop.php?catoid=15&coid=36541) (C- or better)
- **Credits**: 3

<a id="4"></a>

### _Description_

A programming intensive introduction to the creation of computer games. Using mostly two-dimensional 
sprite-based programming, we examine and experiment with animation, physics, artificial intelligence 
and audio. In addition, the course explores the mathematics of transformations (both 2D and 3D) and 
the ways they may be represented.

<br>

<a id="5"></a>

### _Objectives_

You will learn about vector, coordinate systems, sprites, animation, collisions, physics, map-building, simple enemy AI, audio and handling user input. This will all be done with C++ programming and utilizing the [**raylib**](https://www.raylib.com/) library, itself a cross-platform OpenGL wrapper. You will be able to create simple 2D games in your engine as well as gain exposure into 3D game programming.

<br>

<a id="6"></a>

### _Computer/Software Requirements_

You need to use either a Mac, Linux, or Windows computer. You do not need a powerful machine as we are
not implementing anything super complicated. While I recommend the use of [**Visual Studio Code (VSCode)**](https://code.visualstudio.com/), you can use whatever you're most comfortable with.

You will also need a [**Github**](https://github.com/) account!

[**Project Setup Instructions**](resources/SET_UP.md)

<br>

<a id="7"></a>

### _Grading Scheme_

| **Item**                                                                | **Percentage** |
|-------------------------------------------------------------------------|----------------|
| **_Project 1_**: **Draw a Simple 2D Scene** | 10%            |
| **_Project 2_**: **Pong**                   | 10%            |
| **_Project 3_**: **Lunar Lander**           | 15%            |
| **_Project 4_**: **Rise of The AI**         | 25%            |
| **_Project 5_**: **Students' Choice**                               | 30%            |
| **_Classwork_**                                                         | 10%            |

- **Projects** (90%)
    - Assigned roughly every two weeks, these are programming projects based on class material and are to be _independently done_. 
    - As you can see, this class is very project-heavy. What this means is that, while there are no exams nor quizzes, the grade of each of the projects has a relatively large impact on your overall course grade.
    - This class assumes a solid understanding of the C++ language, including syntax, control flow, functional decomposition, and object-oriented programming. For this reason, we will not be grading you on the quality of your code. 
    - However, as the raylib library is quite expansive and as there are multiple ways of approaching it, you are expected to _only use structures that we have learned in class_. For example, if we define a specific class during lecture, and we require its use in a project, **you must use it for full credit**. 
    - Of course, if you are free to make your own modifications and create any auxiliary functions/classes/libraries to best suit your programming style. If you are ever unsure of whether you are allowed to use something in a homework project, please ask us first.
    - Every assignment will have an "extra credit" portion. This will **add 5% to your final grade** at the end of the semester if you complete the extra credit portion of **at least 3 of the projects**. While 5% may not seem like a lot, it can mean the difference between two letter grades. This can be especially helpful later in the semester, when the projects become longer and more complex.

- **Classwork** (10%) is based on 5-7 group assignments to be completed, as the name implies, during class. In order to get credit for these, you will need to:
    1. Be there.
    2. Complete the assignment with your team _before_ the end of class.
    3. Complete the assignment using only structures learned in class.
    4. Ensure that at least one person in your team shows the finished solution to the professor.

As for your final letter grade, the following scale will be used:

| **Letter Grade** | **A**  | **A-** | **B+** | **B** | **B-** | **C+** | **C** | **C-** | **D+** | **D** | **F** |
|------------------|--------|--------|--------|-------|--------|--------|-------|--------|--------|-------|-------|
| **Range**        | ≥95 | ≥90  | ≥87  | ≥83 | ≥80  | ≥77  | ≥73 | ≥70  | ≥67  | ≥60 | ≥0  |

**There is no additional extra credit** in this course and the grades are **not curved**.

<br>

<a id="8"></a>

### _Deadlines, Extensions, and Late Work Policy_

- All projects are due at **11:59pm on Saturdays**.
    - Late projects will have **10 points deducted per day**. 
    - Late projects will not be accepted after **2 days**.
    - Due by 11:59pm means your project was successfully pushed to GitHub _by that time_. This means that the version to be graded must be uploaded in both Brightspace and GitHub at that time. Start pushing your project at least an hour before the deadline.
    - Projects received **1 minute late** are considered to be **a day** late.

- If there are any issues with uploading your project, you must email me **24 hours prior to the due date**.
    - While I check email regularly, do not expect a response over the weekend or close to deadlines.
    - Your code must compile. Code that does not compile will receive a grade of 0.

- You may ask for an extension for **any 2 of your 5 projects**. The extension policy varies per project:
    - **Projects 1-3**: You may ask for an informal extension by asking Prof. Romero Cruz at least 72 hours (3 days) before the deadline. The exact length of the extension will be assigned on a case-by-case basis.
    - **Project 4**: You _must_ contact the [**Office of Student Advocacy**](https://engineering.nyu.edu/life-tandon/student-life/student-advocacy) in order to request an extension for this project, since its deadline coincides with the start of your work on your final project. If they approve it, then I will grant it with no problem at all.
    - **Project 5**: Your final project is graded _during the last day of lecture_, when you will present it to the class. This means that no extensions are, in theory, possible. However, should an emergency arise, I can grant you an incomplete grade (`I`) for the time being and give you a short extension. This really is a last-resort option, so try to avoid it as best as possible.

<a id="8-1"></a>

#### Project Schedule

| Project                 | Release Date        | Due Date                    |
|-------------------------|---------------------|-----------------------------|
| **Simple Scene**        | Friday, Feb 6       | Saturday, Feb 14, 11:59PM   |
| **Pong**                | Friday, Feb 13      | Saturday, Feb 28, 11:59PM   |
| **Lunar Lander**        | Friday, Feb 27      | Saturday, Mar 14, 11:59PM   |
| **Rise of the AI**      | Friday, Mar 13      | Saturday, Apr  4, 11:59PM   |
| **Students' Choice**    | Friday, Apr  3      | Saturday, Apr 24, 11:59PM   |

<br>

<a id="9"></a>

### _Getting Help and Slack_

If you are emailing me for help with your projects, upload your entire project to github and email me with the link (I need to see everything so I can help you). Do not email screenshots of your code. 

**Slack Server**: We will be using Slack to answer quick questions that you may have about the course throughout the semester; the join link will be provided during the first day of class. While I’m usually pretty lax in terms of behavior in our server, this server is still a university environment and should be treated as such. Be respectful to me, your course assistant, and to your fellow students. Please adhere to the following rules:

- Do not post your homework assignment code, or anybody else's, on this server. Doing so will have you automatically banned and flagged for plagiarism. You may, however, share small code blocks that don’t give away your implementation in order to ask questions.

- Please use your real first and last name as your name for easy identification.

- While we aim to be as active as possible on this server, we may not always have time to respond to a question. Please respect the team’s time as you wait for somebody to answer your question. As a student of this class, you should aim to try to answer your classmates' questions as well, instead of waiting for me to answer them every single time.

- This is a productivity server. While we encourage a relaxed atmosphere, let's stay on topic. For absolutely necessary off-topic content (it happens), post in `#off-topic`.

- Use `#concepts-help` to ask questions that pertain to the lecture material in general (i.e. not specific to a project).

- Use `#projects` to ask questions that pertain to the project concepts in general.

- Do NOT use this server to rant about your performance in the class. This is a professional environment, and so such behavior will result in a ban. If you would like to discuss your grades, schedule office hours with me.

- You may not invite any people outside of our class into this server.

<br>

<a id="10"></a>

### Moses Center Statement of Disability

If you are a student with a disability who is requesting accommodations, please contact New York University’s Moses Center for Students with Disabilities (CSD) at 212-998-4980 or **mosescsd@nyu.edu**​. You must be registered with CSD to receive accommodations. Information about the Moses Center can be found at [**Moses Center for Accessibility and Inclusive Culture**](https://www.nyu.edu/life/community-flourishing/centers-and-communities/accessibility.html)​. The Moses Center is located at 726 Broadway on the 3rd floor.

Accommodations matter a _lot_ for this class, so please don't hesitate.

<br>

<a id="11"></a>

### Academic Integrity

NYU School of Engineering Policies and Procedures on Academic Misconduct [**Student Code of Conduct**](https://engineering.nyu.edu/life-tandon/student-life/student-advocacy/student-code-conduct).

- **Introduction**: The Tandon School of Engineering encourages academic excellence in an environment that promotes honesty, integrity, and fairness, and students at the Tandon School of Engineering are expected to exhibit those qualities in their academic work. It is through the process of submitting their own work and receiving honest feedback on that work that students may progress academically. Any act of academic dishonesty is seen as an attack upon the School and will not be tolerated. Furthermore, those who breach the School’s rules on academic integrity will be sanctioned under this Policy. Students are responsible for familiarizing themselves with the School’s Policy on Academic Misconduct.

- **Definition**: Academic dishonesty may include misrepresentation, deception, dishonesty, or any act of falsification committed by a student to influence a grade or other academic evaluation. Academic dishonesty also includes intentionally damaging the academic work of others or assisting other students in acts of dishonesty. Common examples of academically dishonest behavior include, but are not limited to, the following:

    - **Cheating**: intentionally using or attempting to use unauthorized notes, books, electronic media, or electronic communications in an exam; talking with fellow students or looking at another person’s work during an exam; submitting work prepared in advance for an in-class examination; having someone take an exam for you or taking an exam for someone else; violating other rules governing the administration of examinations.

    - **Fabrication**: including but not limited to, falsifying experimental data and/or citations.

    - **Plagiarism**: intentionally or knowingly representing the words or ideas of another as one’s own in any academic exercise; failure to attribute direct quotations, paraphrases, or borrowed facts or information.

    - **Unauthorized collaboration**: working together on work that was meant to be done individually.

    - **Duplicating work**: presenting for grading the same work for more than one project or in more than one class, unless express and prior permission has been received from the course instructor(s) or research adviser involved.

    - **Forgery**: altering any academic document, including, but not limited to, academic records, admissions materials, or medical excuses.

<a id="11-1"></a>

#### Generative AI

You can only learn from the work from the work that you actually do yourself. CS 3113 is an intro class—the 1114 of game development. The goal here is for you to learn the very basic building blocks of a trade.

So, you may be wondering: can I use generative AI (gen AI) in this class? This short answer is that, most of the time, _no, you cannot_. The long answer is more nuanced, given the omnipresence and easy-of-use of tech like ChatGPT and Copilot. My general advice is to use your common sense: _is gen AI doing most of the work for you_? If so, then you are likely in the danger zone, at least as far as this course is concerned.

In our opinion, we're not doing _anything_ in CS 3113 that warrants the use of gen AI. However, in order to minimize ambiguity, please abide by the following rules and you will be fine:

1. **Do not enter the project prompts, class notes, or my code into any gen AI engine**. While is isn't an act of plagiarism, it is unauthorized use of university (and our) materials.
2. **Do not prompt gen AI with project requirements and use the resulting code**. _This is plagiarism_, full stop. Plus, even if you paraphrase our instructions instead of using our prompts directly, raylib is still a really large library; chances are that the code that gen AI will give you will be so irreconcilable with our course's that catching plagiarism will be a non-issue. Please, don't even think about it.
3. **If you absolutely must use gen AI, do so smartly and let Prof. Romero Cruz know**. If you really want to use gen AI for something not directly related to or taught in the class (i.e. path-finding algorithms, etc.), do the following:
    1. Ask Prof. Romero Cruz.
    2. In your code, cite the use of whichever gen AI technology you used. For example:
    ```c++
    /*
     * This algorithm was generated using ChatGPT using the following prompt:
     *  ...
     *  ...
     **/
    ```

It's also worth remembering that a single 100-word ChatGPT-4 response uses the equivalent of [**a whole 500ml bottle of water**](https://www.techrepublic.com/article/generative-ai-data-center-water-use/), with [**ChatGPT-3 not doing much better**](https://arxiv.org/pdf/2304.03271). This may or may not sound like a lot, but with a [**quarter of the world's population having no access to potable water**](https://www.who.int/news/item/26-08-2025-1-in-4-people-globally-still-lack-access-to-safe-drinking-water---who--unicef), it might be worth reserving the use of generative AI for things that actually need it and not to generate code that will give you an F in this class.

<a id="11-2"></a>

#### Penalties

If we determine that you plagiarized in any way, with or without gen AI, the following penalties will be handed out, with no exceptions:

- The penalty for 1st instance of plagiarism is an 0 on that project and an academic dishonesty report to the CSE department.
- The penalty for a 2nd instance of plagiarism will result in an F for the course and 2nd report to the CSE department.