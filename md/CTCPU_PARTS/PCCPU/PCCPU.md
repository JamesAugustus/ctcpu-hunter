# PCCPU

James Augustus

## In one sentence

PCCPU is a separate controller unit that does no calculation and hands out the work. It is a design I am still working on. It is not finished, and I have not placed it in the single core version of Hunter.

## The idea

My older CT-CPU design had 4096 cores. I added a 4097th core to them and called it PCCPU (Program Counter CPU). It does not calculate, it blows the whistle. It sets the rhythm, which is the clock. It keeps the order, which is the counter. It says who gets what, which is the address. It does not have to know what is inside an instruction, it only hands it out. It is like a traffic officer or a card dealer.

I corrected a mistake in the design. At first I thought PCCPU fed an instruction on every clock tick. Feeding four thousand cores one by one would be a bottleneck. What is right is this: PCCPU starts the work and steps back, the cores work independently, and each one has its own counter and its own loop. PCCPU is only called back when something concerns the outside: when there is an overflow, when data has to pass between cores, when a job is finished and when synchronisation is needed. The whistle blower says "start", and the athletes do their own training. The whistle blows only for a collision, for time or for a change, it does not call out every movement.

## Three ways of working

In the central way, PCCPU sends every instruction one by one and the cores do what they are told. It is sequential, with no parallelism. In the independent way, PCCPU hands out the work and watches, and each core runs its own program. In the cube and leader way, the cores are split into cubes, PCCPU talks only to the leaders, and the worker cores only calculate.

I think choosing one way is wrong, the three should work together. When the system starts I load the data in the central way, then I build the cubes, the idle cores work independently, and PCCPU decides which one is active and when.

## What is still open

Where the program is kept is open: in the registers, in a small instruction buffer in every core, or broadcast from PCCPU. Where PCCPU itself sits is open too: outside the grid, inside it, or in software. What goes inside it is still under discussion: a program counter, an address decoder, an instruction decoder, and maybe a table that records whether each core is busy or idle. Whether more than one PCCPU is needed I will look at later, starting with one and checking again if a bottleneck appears.

Hunter is a single core today. There, the place of the instruction source and the program counter is not decided yet. I do not put the old PCCPU into that gap as a finished part. This document describes where the design stands now, it does not show a tested circuit.
