## Task 7: The LD PRELOAD Environment Variable and Set-UID Programs:
Several environment variables, including `LD PRELOAD`, `LD LIBRARY PATH`, and other `LD_*` influence the behavior of **dynamic loader/linker**.

A **dynamic loader/linker** is the part of an operating system (OS) that loads (from
persistent storage to RAM) and links the shared libraries needed by an executable at run time.

In Linux, `ld.so` or `ld-linux.so` are the dynamic loaders that handle loading shared libraries. Two key environment variables affect this process:

| | |
| -------- | --------- |
| `LD_LIBRARY_PATH` | Specifies directories to search for libraries before the default paths. |
| `LD_PRELOAD` | Forces specific user-specified libraries to load before others. |