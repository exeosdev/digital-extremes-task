Author: Mateusz Grzejek

This is my solution for the programming task I've received couple days ago. Since it was a two-step process, here we go:

*Part 1 (bug-fixing and refactoring)*
- Missing virtual destructor for PowerUp while using the base pointer to keep power ups in the container means that only base destructor would be called even if we properly deleted all power ups (added).
- Using plain char[] buffer with explicit allocation probably not a good idea either. No performance gain compared to std:: solutions (replaced with std::string).
- No point in explicit assignment of the PowerUp's mType in the constructors' bodies. The type is fixed for a given PU instance, so passing it also via initialisation list is way more correct (fixed).
- Better ownereship semantics for objects: storage containers use std::unique_ptr<> for keeping the objects alive which also automatically handles de-allocation. For public API I used plain pointers instead - lifetime is properly managed, so there is no need to use any explicit shared ownership.
- Static variables from main file turned into local variables.
- Probably few more minor fixes.

*Part 2 (path finding)*
- I implemented classic DFS algo. Second commit (with initial version) contains recursive version which I then replaced with iterative one. Since recursion can be stack-heavy, I wanted to eliminate possibility of a big footprint (or even stack overflow) in case of huge graphs.
- I used unordered_set for marking nodes traversal because of its (ideally) O(1) complexity. I used pointers directly as keys, which is another performance-friendly thing (no complex hashing involved).
- The markup table (a mentioned set) grows of course as we traverse the graph so there is an O(n) memory footprint involved.
- I kept the original test (but enclosed in local scope) and added few extra ones to test some cases I thought could be tricky.

I hope you enjoy looking at it!

Mateusz