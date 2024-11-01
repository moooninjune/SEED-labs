## Task 7: The LD PRELOAD Environment Variable and Set-UID Programs:
A **dynamic loader/linker** is the part of an operating system that loads (from storage to RAM) and links the shared libraries needed by an executable at run time.

In Linux, `ld.so` or `ld-linux.so` are the dynamic loaders that handle loading shared libraries. **Two key environment variables affect this process:**
| Variable | |
| -------- | --------- |
| `LD_LIBRARY_PATH` | Specifies a list of directories that the dynamic linker should search first when looking for shared libraries before the default paths. |
| `LD_PRELOAD` | Forces the dynamic linker to load specific user-specified libraries before any others, regardless of where they are. |