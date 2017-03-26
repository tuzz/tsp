## Travelling Salesperson

I spent a couple of weekends working on
[this challenge](https://travellingsalesman.cz/). I didn't enter my attempts for
the competition, but enjoyed spending some time getting to grips with the C
programming language.

My first attempt was to reduce the problem to a Partial Weighted-MaxSAT problem
and then feed it to a Satisfiability solver via
[Open-WBO](http://sat.inesc-id.pt/open-wbo/). This was successful, but slow in
practice.

My second (unfinished) attempt was to write a genetic algorithm based on an
approach discussed in
[The New Turing Omnibus](http://www.goodreads.com/book/show/964709.The_New_Turing_Omnibus).
I didn't finish this, but managed to encode the problem and seed the first
generation.

If you'd like to run these programs, you should be able to run `make` for each
subdirectory then run with `./run < data_10.txt`. More example inputs can be
found on the challenge page.
