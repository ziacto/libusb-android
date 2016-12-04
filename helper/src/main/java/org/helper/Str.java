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


    public static String lpad(String string, int size) {
        return lpad(string, size, " ");
    }

    public static String lpad(String string, int size, String padding) {
        if (string.length() > size) {
            return string.substring(0, size-3) + "...";
        }
        String pad = "";
        while ((pad + string).length() < size) {
            pad += padding;
        }
        return pad + string;
    }

    public static String rpad(String string, int size) {
        return rpad(string, size, " ");
    }

    public static String rpad(String string, int size, String padding) {
        if (string.length() > size) {
            return string.substring(0, size-3) + "...";
        }
        String pad = "";
        while ((pad + string).length() < size) {
            pad += padding;
        }
        return string + pad;
    }

}
