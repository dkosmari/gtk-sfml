#ifndef FONT_HPP
#define FONT_HPP

// we use ld to embed the font file into an object, it has these symbols:
extern const char _binary_LiberationSans_Regular_ttf_start[];
extern const char _binary_LiberationSans_Regular_ttf_end[];
extern const char _binary_LiberationSans_Regular_ttf_size[];


#define FONT_DATA (&_binary_LiberationSans_Regular_ttf_start)

#define FONT_SIZE                                                               \
    ((&_binary_LiberationSans_Regular_ttf_end[0]) - (&_binary_LiberationSans_Regular_ttf_start[0]))


#endif
