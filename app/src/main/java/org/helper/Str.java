/**
 * License Public Domain (CC0) 2016 Julio Tentor (jtentor@gmail.com)
 *
 * To the extent possible under law, Julio Tentor has waived all copyright and related
 * or neighboring rights. This work is published from: Jujuy - Argentina.
 *
 * http://creativecommons.org/publicdomain/zero/1.0/
 *
 */

package org.helper;

public class Str {
    public Str() {
    }

    /**
     * Left padding with space character
     *
     * @param string original string
     * @param size max size
     * @return a new string, left padded with space character and "size" max length
     */
    public static String lpad(String string, int size) {
        return lpad(string, size, " ");
    }

    /**
     * Left padding
     *
     * @param string original string
     * @param size max size
     * @param character character to add
     * @return a new string, left padded with char "character" and "size" max length
     */
    public static String lpad(String string, int size, String character) {
        if (string.length() > size) {
            return string.substring(0, size-3) + "...";
        }
        StringBuilder pad = new StringBuilder(size);
        for (int c = string.length(); c < size; ++c) {
            pad.append(character);
        }
        pad.append(string);
        return pad.toString();
    }

    /**
     * Right padding with space character
     *
     * @param string original string
     * @param size max size
     * @return a new string, right padded with space character and "size" max length
     */
    public static String rpad(String string, int size) {
        return rpad(string, size, " ");
    }

    /**
     * Right padding
     *
     * @param string original string
     * @param size max size
     * @param character character to add
     * @return a new string, right padded with char "character" and "size" max length
     */
    public static String rpad(String string, int size, String character) {
        if (string.length() > size) {
            return string.substring(0, size-3) + "...";
        }
        StringBuilder pad = new StringBuilder(size);
        pad.append(string);
        for (int c = string.length(); c < size; ++c) {
            pad.append(character);
        }
        return pad.toString();
    }
}
