<h2 align=center>Week 11</h2>

<h1 align=center>Playtesting</h1>

<h3 align=center>14 Red Wolf Moon, Imperial Year MMXXV</h3>

<p align=center><strong><em>Song of the day</strong></em>: <em><a href="https://youtu.be/NRKznQXtBn4?si=fc3j-BYME5y-iXgJ"><strong><u>中南海 (Live at the Powerhouse Arena, Brooklyn)</u></strong></a> by Carsick Cars (2009)</em></p>

---

## Sections

1. [**What Is Playtesting?**](#1)
2. [**The Playtester Is Not Wrong**](#2)
3. [**The Trap of the Predicate Survey**](#3)
4. [**Building a Survey That Actually Tells You Something**](#4)
    - [**Calibration**](#4-1)
    - [**Experience**](#4-2)
    - [**Specific Design Questions**](#4-3)
    - [**Open Invitation**](#4-4)
    - [**Putting It Together**](#4-5)

---

<a id="1"></a>

## Part 1: _What Is Playtesting?_

Every creative medium has some version of this problem: the person who made the thing cannot experience it the way a stranger will. A novelist can't un-know their own plot. A film editor stops seeing the cut after the twentieth pass. Game developers have it especially bad, because games are interactive, and the more you play your own game, the more your muscle memory and prior knowledge mask every point of friction that would stop a new player cold.

Playtesting is the structured practice of putting your game in front of people who are not you, and paying close attention to what happens.

It lives inside the broader **game development cycle**, typically running in parallel with production rather than after it:

1. **Prototype** — a rough version built to test a single idea or mechanic
2. **Playtest** — real players interact with the prototype; you observe and collect feedback
3. **Analyze** — you identify patterns in what you observed and what players reported
4. **Iterate** — you change the game based on what you learned, then playtest again

That loop repeats. A common shorthand in the industry is: the last 10% of polish takes as long as the first 90% of building. Playtesting is how you find out what that 10% actually is.

It's worth distinguishing playtesting from two things it's often confused with:

- **QA testing** (Quality Assurance) is about technical correctness—finding crashes, broken collision, audio that doesn't trigger, save data that corrupts. QA happens close to ship. Playtesting happens throughout development, and its subject is the *experience*, not the *stability*.
- **User research / focus groups** are about gathering opinions on what players *want*. Playtesting is about observing what players *do* and understanding why. The distinction matters: players are often wrong about what they want but never wrong about what they felt.

The earliest playtesting should happen embarrassingly early — before the art is done, before the levels are balanced, sometimes before the mechanics are fully implemented. The longer you wait, the more attached you become to decisions that might need to change, and the more expensive those changes become.

<br>

<a id="2"></a>

## Part 2: _The Playtester Is Not Wrong_

The number one mistake designers make in their first playtesting session is this: they watch someone struggle with their game, and they start explaining it.

**Don't.**

The moment you open your mouth to clarify a mechanic, you have invalidated the session. You've learned that without your explanation the mechanic was confusing — and then you've erased that data by providing the explanation. The rule is simple:

> _If your game needs you standing next to it to work, your game doesn't work._

Playtesting is not a demo. You are not showing off. You are observing. Your job is to be a fly on the wall while another human being interacts with the artifact you built, and to come away with enough honest information to make it better.

This is psychologically difficult. Watching someone be confused by, bored with, or indifferent to something you spent weeks on is uncomfortable. Your instinct will be to defend, redirect, or explain. That instinct is the enemy of useful feedback. Kill it.

What playtesting actually is:

- **A diagnostic tool.** It surfaces gaps between what you intended and what the player experiences.
- **An empathy exercise.** It forces you to see your game through eyes that don't share your context — your months of building it, your mental model of how it "should" be played.
- **An iterative checkpoint.** Every session should give you a short list of concrete things to address before the next one.

What it is not:

- **A focus group.** You are not asking players what game they want you to make. That's a different job, and asking playtesters to design your game for you produces bad games.
- **A validation session.** "Did people like it?" is not a research question. You already know the answer is "some did, some didn't." That tells you nothing about what to fix.
- **QA testing.** QA is about finding bugs. Playtesting is about finding friction — moments where the game breaks the player's sense of agency, understanding, or fun.

During the session itself, try to keep quiet and take notes. What did the player try that didn't work? Where did they slow down? Where did they speed up? Did they read the UI? Did they laugh, sigh, lean forward? These observations are often more valuable than anything they write in a survey afterward, because behavior is harder to rationalise than opinion.

<br>

<a id="3"></a>

## Part 3: _The Trap of the Predicate Survey_

After the session, you need a survey. And here is where most student projects produce useless data.

The trap is the **predicate question** — a question that smuggles its answer in the premise:

- _Did you find the controls easy to use?_
- _Did you enjoy the boss fight?_
- _Was the tutorial helpful?_

These are yes/no questions with a built-in "correct" answer. Playtesters—especially classmates who know you—will default to the answer they think you want to hear. Even if they answer honestly, "no" tells you nothing. No, the controls weren't easy — but why? Which control? What did you try first? What did you expect?

The second trap is the **pure rating scale**:

- _Rate the overall difficulty from 1 to 5._
- _How fun was the game? (1–10)_

Rating scales are seductive because they produce numbers, and numbers feel like data. But a 6/10 on fun is not actionable. You cannot open your code and fix a 6/10. What caused it? Was the first level too slow? Did the player die three times in a row and get frustrated? Did the music loop annoyingly? You don't know, because you asked the wrong question.

The third trap is the **wish list question**:

- _What would you add to make the game more fun?_
- _What should I change?_

This hands the design problem to someone who has played your game for 10 minutes. They will suggest things that sound reasonable in the abstract but would require months to build or would break the game's existing balance. Their suggestions aren't useless—but they're not the point. The point is understanding what *caused* them to want something different, not what that something is.

What I'm trying to say here is:

> **A good playtesting question asks the player to recall or describe an experience. A bad one asks them to evaluate or prescribe.**

Evaluation and prescription are your jobs. The player's job is to be a witness to their own experience.

<br>

<a id="4"></a>

## Part 4: _Building a Survey That Actually Tells You Something_

A well-structured playtesting survey has four parts. Think of it as a funnel: you start wide (who is this person?), move to their general experience, narrow into specific design questions, and then open back up at the end.

<a id="4-1"></a>

### Calibration

Before asking about your game at all, ask a question or two that tells you _who_ your playtester is. This matters because the same game experience reads differently depending on a player's background.

> _Roughly how often do you play games? (Rarely / A few times a month / A few times a week / Daily)_

> _What genres do you usually play? (Check all that apply: Platformers, RPGs, Puzzle, Strategy, Shooters, I don't play games often)_

This isn't small talk; it's context. If your die-hard action gamer says the combat feels slow and your casual player says it's overwhelming, those are two very different design signals that point toward different solutions.

<a id="4-2"></a>

### Experience

Immediately after play, while the feeling is still fresh, ask about the emotional arc of the session before you ask about mechanics. Feelings first, details second.

The best experience questions use **behavioral recall** — they ask the player to describe what happened, not to rate it:

> _Describe a moment during the game where you felt stuck or unsure what to do next. What were you doing when that happened?_

> _Was there a moment where you felt like you were "getting it"—where something clicked? If so, what was happening?_

> _What was going through your mind the first time you saw the [main mechanic / enemy / level transition]?_

Notice that none of these ask "did you like X." They ask the player to put themselves back in a specific moment and describe it. That description will tell you far more than a rating. A player saying "I didn't realise I was supposed to jump on the platforms, I thought I needed to go left" is infinitely more useful than "3/5 on clarity of objectives."

<a id="4-3"></a>

### Specific Design Questions

Now that you have their overall experience in mind, you can ask targeted questions about the specific things you're uncertain about. These should be different for every project—**tailor these to your actual open design questions**, not generic game quality metrics.

For example, if you're unsure whether your tutorial communicates effectively:

> _Without looking anything up, can you describe in your own words how [mechanic X] works? No worries if you're not sure._

If you're testing level pacing:

> _At what point during the game did you feel most engaged? What about least engaged?_

If you're testing difficulty calibration:

> _How many times did you fail before succeeding at [specific challenge]? How did that feel—frustrating, fair, easy?_

If you have a rating scale question, **always anchor it.** A scale from 1 to 5 with no labels is noise. Tell the player what 1 means and what 5 means:

> _How challenging did you find the game overall?_
> _(1 = I never felt threatened / 5 = I felt overwhelmed and didn't know how to proceed)_

Now a "3" means something.

<a id="4-4"></a>

### Open Invitation

End every survey with one or two open-ended questions that give the player space to say anything you didn't think to ask. Keep them brief:

> _Is there anything about the game that surprised you—positively or negatively?_

> _Anything else you'd like to tell the developer?_

These often beget the most valuable feedback precisely because they're unconstrained. A player who felt fine about everything you asked might mention, unprompted, that the sound effect on the jump was startling in a way that made them anxious. You would never have thought to ask.

<a id="4-5"></a>

### Putting It Together

When you build your survey, here are some practical choices to make:

- **Short answer** is for brief factual responses (genre, game frequency). Don't use it for experience questions—it's too cramped and signals to the respondent that you want a short reply.
- **Paragraph** is for any question where you want a real answer. Use this for behavioral recall and open invitation questions.
- **Linear scale** is for your anchored rating questions. Always label both ends. Always make these optional—a player who can't decide between a 3 and 4 will just pick randomly, which pollutes your data.
- **Multiple choice / Checkboxes** are for calibration questions where you already know the possible answers.
- **Mark questions as required sparingly.** If a question is hard to answer—"describe a moment where you felt stuck"—making it required causes players to rush through it. A thoughtful optional response beats a hasty required one.

Finally: keep it short. Five to eight questions is enough. A long survey trains your players to answer carelessly. If you have twelve questions you care about, run two sessions and split them.

<br>

---

### Questions that work vs. questions that don't

| Doesn't work | Works — and why |
|---|---|
| _Did you enjoy the game?_ | _What was the most memorable moment from your session?_ (asks for a specific, not a judgment) |
| _Was the game too hard or too easy?_ | _How many times did you die or fail before reaching the end? How did that feel — fair, frustrating, or easy to brush off?_ (grounds difficulty in actual events) |
| _Did you like the art style?_ | _Was there a visual element that stood out to you—positively or negatively?_ (open enough to catch things you didn't expect) |
| _Would you recommend this game?_ | _Who do you think this game is for? What kind of player would enjoy it most?_ (reveals your audience perception) |
| _What should I add to make it better?_ | _Was there a moment where you wanted to do something and couldn't? What were you trying to do?_ (identifies friction without outsourcing design decisions) |
| _Rate the controls from 1–5_ | _When you first picked up the controls, was there anything that didn't respond the way you expected? If so, what did you try?_ (finds the specific moments of confusion) |

<br>

The goal is not to get players to tell you your game is good. The goal is to understand, with as much specificity as possible, what it felt like to be them playing it, so that you can close the gap between the experience you designed and the experience they had.
