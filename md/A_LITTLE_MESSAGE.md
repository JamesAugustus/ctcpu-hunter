# A Little Message

This section contains historical goals alongside later assessments. Its statements about the emulator, ISA, scoreboard, cycles and performance were not retested in this package. The date 18 July below does not mean every sentence was written that day. The old CT-CPU design described here and the Hunter in the research journal belong to different stages of the project.

### What I want, my aims, what I want to do (18 July 2026)

#### Who I am and where I come from

Throughout my life I have loved data packaging, practical communication and optimisation. I enjoy thinking about how things can be done interactively and indirectly in parallel. I like to consider the reasoning on the other side of an argument. I have often weighed even other people's cause-and-effect relationships in my mind. I try to establish context through different meanings by looking straight and diagonally across a grid (my Scrabble/crossword principle). I am preoccupied with data transfer, even communication between people and with other living beings. I sense someone's sincerity as they speak. My perception works as a whole. Lately I have not communicated very well with people, because I too become impatient. I lose interest when I meet forms of communication that are insincere, clumsily disguise their intent, arise from sudden impulse and try to give the impression of interest.

I enjoy working out how a system works. Format conversion and reverse engineering are areas I feel at home in. x64/ARM assembly, file formats, reading binary. That is where I come from. My new projects continue that experience.

As a child I learned that the established arrangement is not always the best design. I tried the F keyboard, and it was a wonderful experience. It had been designed for Turkish, after all. But the world had grown used to QWERTY, and an industry had been built around it. I had to adapt too, so I started using Turkish QWERTY. When I realised that English QWERTY was faster for my current work, and that the field I work in had been built around that keyboard, I recently adapted to English QWERTY.

I call this the QWERTY effect. Once an arrangement becomes widespread, everyone gets used to it and tools are built around it. A better design loses if it cannot beat the cost of switching.

#### My big dream: a computer that breathes deeply

My aim is a machine that wins through calmness, not speed. I imagine a 3 GHz processor devoting a third of its capacity to planning and organising the work, and the remaining two thirds to solving larger problems. More work should get done, with a little calm thought along the way. The 1 GHz / 2 GHz split is an analogy: GHz is not a unit of energy, and this ratio is not a measured result. I call this the deep-breathing policy.

Here is my metaphor. A fast, manic professional player may be good. An experienced but calm player with clean mechanics will always play even better. I am designing the calm player. Anyone interested can look up the FPS player Dfalt_.

Asking the same question does not mean setting the same thinking process in motion. When I ask two systems to “pick a number,” the algorithms they use shape their choices. I think culture, habits and lived experience have a similar influence on people. People who share common ground may gravitate towards similar choices and paths of discovery, even without knowing about one another. This is part of what I mean by the mechanics of thinking.

This machine will do exact mathematics, with zero floating-point error. I have symbolised the numbers. Every number lives in two forms at once: positional form (for addition) and shadow form, meaning prime-factor exponents (multiplication = exponent addition, division = exponent subtraction, root = halving exponents). I also carry things such as √x, i√x, 1/x, Σx, x! as TYPES, not operations. They are carried symbolically and expanded when needed. Storing, interpreting and expanding the representation have costs.

A short description of the machine: [CTCPU](CTCPU.md).

There is no silicon. All MHz/watt/cycle numbers are model estimates. Only emulator measurements are real and are labelled as such. I will not hide this sentence. I will put it at the very top of the README.

I also know and state my limits. Shadow cannot add, but I am working on a few things. It does not fly on random data (I calculated this myself: the part of a random number contributed by the first seven primes has an average logarithmic size of about 3.75 bits), and 120 KB of memory is small for general-purpose work. I focus on structured numbers and exact arithmetic. Gröbner computations, exact rational arithmetic and monomial engines are possible applications. My goal is zero rounding error. The costs and limits of that goal must be measured together with the chosen data types and comparison computations. By itself it does not prove superiority to other computing units.

I am designing a calm coprocessor that takes work from a host computer and focuses on particular calculations. I will not compete at the same table as the established giants. I will play with letters that have no keys on their keyboard.

#### My strategy: emulation, not a processor

I want people to try the emulator first. I ask no one to buy hardware or change habits. My emulator will run on the machines people already have. The installed base will be my carrier, not my enemy (the JVM/WASM/PICO-8 route).

My claim will be measurable and without excuses. I want to compare my emulator with suitable GMP/FLINT methods on the same machine, measuring both time and energy consumption. No "there is no silicon" excuse.

I bought an FPGA board (Tang Nano 9K). Alongside emulation, I will run experiments on FPGA too, but there are things that need to settle first. The first step will be simple. I will proceed in small steps.

#### What I will do (toolchain)

I am working on writing my own assembly language for CT-CPU: textual syntax and an assembler that feeds it into the emulator. The groundwork is ready: ISA opcodes, instruction format, my ARM/x64 representation files.

I will create C equivalents so programmers can enter from a language they know.

I will even make ARM and x64 assembly mappings, with translation tables and bridges.

I will align the emulator one-to-one with the ISA (the known 11.1 inconsistency: the emulator's 22-opcode enum will be brought into the locked 8-opcode map). In the publication, the contract and the code will verify one another.

#### My dream for publication and community

I will put everything that is ready openly on GitHub, including the ISA document, because I want other people to develop it too.

For me, the value lies not only in the product, but also in my ability to create it. I can make something much better, and entirely different architectures too.

My dream is for programmers and people who enjoy optimisation to take the open code and assembly and change them. I want them to try things I have not thought of and build something new. I want what happened to the demoscene, Chip-8 and uxn to happen to my machine too.

And this process will show something: knowing a programming language and using AI do not, on their own, make someone a programmer. Desire and problem-solving make someone a software engineer / computer scientist. The work I do with tools will be evidence of that.

#### God does not play dice

“God does not play dice,” Einstein said. I use it as an analogy for the deterministic behaviour I want in my machine. According to the archive record, kat12 was byte-for-byte identical across four runs. This package does not reproduce that experiment. In the recorded runs, rounding error was zero and deviation from determinism was zero. A machine that does not play dice. Personally, I believe that dice are not rolled in quantum physics either. I believe in string theory.

Alongside all this, I have a personal aim: to pursue my academic goals without worrying about making ends meet. To put my thoughts on paper without thinking about my family's financial difficulties. I want to advance in my education and develop myself within a more orderly system. I am looking for work, an internship, things that will help me develop. These writings also show how scattered my thinking becomes. My excitement and lack of discipline become obstacles on the way to my intuitions and goals.

---

I used artificial intelligence while compiling this document. Because I have tons of files and pages of physical notes, but nobody beside me.

James Augustus
