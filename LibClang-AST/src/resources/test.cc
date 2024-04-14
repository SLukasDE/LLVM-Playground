// test.cc
// Test for deleted-ctor.exe.

// Explicit ctor, not deleted.
class END {
public:
  END();
};

// Explicit ctor, deleted.
class ED {
public:
  ED()=delete;
};


// Implicit ctor, not deleted.
class IND {
public:
};

// Implicit ctor, deleted.
class ID {
public:
  int &i;
};

// EOF
