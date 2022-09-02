#ifndef UMKA_RUNTIME_SRC_H_INCLUDED
#define UMKA_RUNTIME_SRC_H_INCLUDED

static const char *rtlSrc = 

"// Umka standard library\n"
"\n"
"// Memory\n"
"\n"
"fn rtlmemcpy(dest, src: ^void, count: int)\n"
"\n"
"fn tobytes*(buf: interface{}): []uint8 {\n"
"    if buf.__self == null {\n"
"        error(\"Buffer is null\")\n"
"    }\n"
"    bytes := make([]uint8, sizeofself(buf))\n"
"    rtlmemcpy(&bytes[0], buf.__self, sizeofself(buf))\n"
"    return bytes\n"
"}\n"
"\n"
"fn frombytes*(buf: interface{}, bytes: []uint8) {\n"
"    if buf.__self == null {\n"
"        error(\"Buffer is null\")\n"
"    }    \n"
"    if selfhasptr(buf) {\n"
"        error(\"Cannot access reference types\")\n"
"    }\n"
"    if sizeofself(buf) != len(bytes) {\n"
"        error(\"Illegal buffer size\")\n"
"    }\n"
"    rtlmemcpy(buf.__self, &bytes[0], sizeofself(buf))    \n"
"}\n"
"\n"
"// File I/O\n"
"\n"
"type File* = ^struct {}\n"
"\n"
"const (\n"
"    seekBegin* = 0\n"
"    seekCur*   = 1\n"
"    seekEnd*   = 2\n"
")    \n"
"\n"
"fn rtlfopen  (name: str, mode: str): File;  \n"
"fn fopen*    (name: str, mode: str): File {return rtlfopen(name, mode)}\n"
"\n"
"fn rtlfclose (f: File): int\n"
"fn fclose*   (f: File): int {return rtlfclose(f)}\n"
"\n"
"fn rtlfread  (buf: ^void, size, cnt: int, f: File): int\n"
"fn fread*    (f: File, buf: interface{}): int {\n"
"    if f == null {\n"
"        error(\"File is null\")\n"
"    }\n"
"    if bytes := ^[]int8(buf); bytes != null {\n"
"        return rtlfread(&bytes[0], len(bytes^), 1, f)\n"
"    }\n"
"    if ubytes := ^[]uint8(buf); ubytes != null {\n"
"        return rtlfread(&ubytes[0], len(ubytes^), 1, f)\n"
"    }        \n"
"    if chars := ^[]char(buf); chars != null {\n"
"        return rtlfread(&chars[0], len(chars^), 1, f)\n"
"    }\n"
"    if selfhasptr(buf) {\n"
"        error(\"Cannot read reference types except ^[]int8, ^[]uint8, ^[]char\")\n"
"    }\n"
"    return rtlfread(buf.__self, sizeofself(buf), 1, f)\n"
"}\n"
"\n"
"fn rtlfwrite (buf: ^void, size, cnt: int, f: File): int\n"
"fn fwrite*   (f: File, buf: interface{}): int {\n"
"    if f == null {\n"
"        error(\"File is null\")\n"
"    }\n"
"    if bytes := ^[]int8(buf); bytes != null {\n"
"        return rtlfwrite(&bytes[0], len(bytes^), 1, f)\n"
"    }\n"
"    if ubytes := ^[]uint8(buf); ubytes != null {\n"
"        return rtlfwrite(&ubytes[0], len(ubytes^), 1, f)\n"
"    } \n"
"    if chars := ^[]char(buf); chars != null {\n"
"        return rtlfwrite(&chars[0], len(chars^), 1, f)\n"
"    }             \n"
"    if selfhasptr(buf) {\n"
"        error(\"Cannot write reference types except ^[]int8, ^[]uint8, ^[]char\")\n"
"    }\n"
"    return rtlfwrite(buf.__self, sizeofself(buf), 1, f)\n"
"}\n"
"\n"
"fn rtlfseek  (f: File, offset, origin: int): int\n"
"fn fseek*    (f: File, offset, origin: int): int {\n"
"    if f == null {\n"
"        error(\"File is null\")\n"
"    }\n"
"    return rtlfseek(f, offset, origin)\n"
"}\n"
"\n"
"fn rtlftell (f: File): int\n"
"fn ftell*   (f: File): int {\n"
"    if f == null {\n"
"        error(\"File is null\")\n"
"    }\n"
"    return rtlftell(f)\n"
"}\n"
"\n"
"fn rtlremove (name: str): int\n"
"fn remove*   (name: str): int {return rtlremove(name)}\n"
"\n"
"fn rtlfeof  (f: File): int\n"
"fn feof*    (f: File): bool {\n"
"    if f == null {\n"
"        error(\"File is null\")\n"
"    }                \n"
"    return bool(rtlfeof(f))\n"
"}\n"
"\n"
"// I/O utilities\n"
"\n"
"fn println*(s: str): int {return printf(\"%s\\n\", s)}\n"
"fn fprintln*(f: File, s: str): int {return fprintf(f, \"%s\\n\", s)}\n"
"\n"
"fn getchar*(): char {\n"
"    var c: char\n"
"    scanf(\"%c\", &c)\n"
"    return c\n"
"}\n"
"\n"
"// Strings\n"
"\n"
"fn ltrim*(s: str): str {\n"
"    start := -1\n"
"    slen := len(s)\n"
"    for i := 0; i < slen; i++ {\n"
"        if s[i] != \' \' && s[i] != \'\\t\' {\n"
"            start = i\n"
"            break\n"
"        } \n"
"    }\n"
"    if start == -1 {return \"\"}\n"
"    return slice(s, start)\n"
"}\n"
"\n"
"fn rtrim*(s: str): str {\n"
"    stop := -1\n"
"    slen := len(s)\n"
"    for i := slen - 1; i >= 0; i-- {\n"
"        if s[i] != \' \' && s[i] != \'\\t\' {\n"
"            stop = i\n"
"            break\n"
"        } \n"
"    }\n"
"    if stop == -1 {return \"\"}\n"
"    return slice(s, 0, stop + 1)\n"
"}\n"
"\n"
"fn trim*(s: str): str {\n"
"    return ltrim(rtrim(s))\n"
"}\n"
"\n"
"// Conversions\n"
"\n"
"fn atoi*(s: str): int {\n"
"    var x: int\n"
"    sscanf(s, \"%lld\", &x)\n"
"    return x\n"
"}\n"
"\n"
"fn atof*(s: str): real {\n"
"    var x: real\n"
"    sscanf(s, \"%lf\", &x)\n"
"    return x\n"
"}\n"
"\n"
"fn itoa*(x: int): str {\n"
"    s := sprintf(\"%lld\", x)\n"
"    return s\n"
"}\n"
"\n"
"fn ftoa*(x: real, decimals: int): str {\n"
"    fmt := sprintf(\"%%.%lldlf\", decimals)\n"
"    s := sprintf(fmt, x)\n"
"    return s\n"
"}\n"
"\n"
"// Math\n"
"\n"
"const pi* = 3.14159265358979323846\n"
"\n"
"// Random numbers\n"
"\n"
"const randMax* = 0x7FFFFFFF\n"
"randSeed := 0\n"
"\n"
"fn srand*(seed: int) {randSeed = seed}\n"
"\n"
"fn rand*(): int {\n"
"    randSeed = ((randSeed * 1103515245) + 12345) & 0x7FFFFFFF\n"
"    return randSeed\n"
"}\n"
"\n"
"fn frand*(): real {return real(rand()) / randMax}\n"
"\n"
"// Timer\n"
"\n"
"fn rtltime(): int\n"
"fn time*(): int {return rtltime()}\n"
"\n"
"fn rtlclock(): real\n"
"fn clock*(): real {return rtlclock()}\n"
"\n"
"// Command line and environment\n"
"\n"
"fn argc*(): int {return rtlargc}\n"
"\n"
"fn argv*(i: int): str {\n"
"    if i < 0 || i >= rtlargc {\n"
"        error(\"Command line parameter not found\")\n"
"    }\n"
"    return rtlargv[i]\n"
"}\n"
"\n"
"fn rtlgetenv(name: str): str\n"
"fn getenv*(name: str): str {\n"
"    return \"\" + rtlgetenv(name)\n"
"}\n"
"\n"
"fn rtlsystem(command: str): int\n"
"fn system*(command: str): int {return rtlsystem(command)}\n"
" ";

#endif // UMKA_RUNTIME_SRC_H_INCLUDED
