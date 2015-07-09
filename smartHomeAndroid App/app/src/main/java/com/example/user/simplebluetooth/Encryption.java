package com.example.user.simplebluetooth;

import java.util.Random;

public class Encryption {
    public static int[] keyTable = {71, 13, 85, 79, 70, 49, 98, 32, 66, 27, 44, 29, 48, 36, 12,
            11, 26, 31, 55, 57, 28, 10, 21, 14, 47, 62, 39, 91, 93, 72, 84, 23, 25, 17, 68, 52,
            87, 75, 78, 50, 89, 37, 77, 61, 51, 86, 45, 41, 64, 60, 42, 16, 53, 20, 15, 35, 76,
            80, 34, 99, 59, 97, 81, 54, 82, 83, 56, 19, 92, 90, 33, 73, 24, 46, 18, 22, 58, 43,
            94, 38, 74, 65, 67, 96, 30, 69, 40, 63, 95, 88,};
    public static int current = 0;

    public static String encrypt(String str) {
        int msg = Integer.parseInt(str);
        int key = keyTable[current];
        String msgStr = getBinaryFromInt(msg) + getBinaryFromInt(msg);
        String keyStr = getBinaryFromInt(key / 10) + getBinaryFromInt(key % 10);
        String revKeyStr = getBinaryFromInt(key % 10) + getBinaryFromInt(key / 10);
        System.out.println("MsgBinary=" + msgStr + " <- " + msg + "(x2)");
        System.out.println("KeyBinary=" + keyStr + " <- " + key / 10 + " " + key % 10);
        StringBuilder sb = new StringBuilder();
        String temp;

        // Message XOR Key
        for (int i = 0; i < msgStr.length(); i++)
            sb.append((msgStr.charAt(i) ^ keyStr.charAt(i)));
        temp = sb.toString();
        System.out.println("msgXORkey=" + temp);
        // Previus XOR KeyReverse
        sb.setLength(0);
        for (int i = 0; i < msgStr.length(); i++)
            sb.append((temp.charAt(i) ^ revKeyStr.charAt(i)));
        temp = sb.toString();
        System.out.println("RevKeyBin=" + revKeyStr + " <- " + key % 10 + " " + key / 10);
        System.out.println("PrevXORrk=" + temp);
        // Previous XOR Key
        sb.setLength(0);
        for (int i = 0; i < msgStr.length(); i++)
            sb.append((temp.charAt(i) ^ keyStr.charAt(i)));
        temp = sb.toString();
        System.out.println("NewXORkey=" + temp);

        /*  DECRYPTION  Msg XOR key -> XOR keyRev -> XOR key
        // Previous XOR Key
        sb.setLength(0);
        for (int i = 0; i < msgStr.length(); i++)
            sb.append((temp.charAt(i) ^ keyStr.charAt(i)));
        temp = sb.toString();
        System.out.println("NewXORkey1=" + temp);
        // Previus XOR KeyReverse
        sb.setLength(0);
        for (int i = 0; i < msgStr.length(); i++)
            sb.append((temp.charAt(i) ^ revKeyStr.charAt(i)));
        temp = sb.toString();
        System.out.println("PrevXORrk2=" + temp);
        // Previous XOR Key
        sb.setLength(0);
        for (int i = 0; i < msgStr.length(); i++)
            sb.append((temp.charAt(i) ^ keyStr.charAt(i)));
        temp = sb.toString();
        System.out.println("NewXORkey3=" + temp);
        */

        temp = sb.toString().substring(0, 4);
        String EncyrptedMessage = Integer.toString(Integer.parseInt(temp, 2));
        System.out.println("EncrypMsg=" + Integer.parseInt(temp, 2));

        System.out.println("------------------------------");
        gotoNextKey();
        return EncyrptedMessage;
    }

    public static String getBinaryFromInt(int value) {
        String a = Integer.toBinaryString(value);
        if (a.length() == 1) {
            a = "000" + a;
        } else if (a.length() == 2) {
            a = "00" + a;
        } else if (a.length() == 3) {
            a = "0" + a;
        }
        return a;
    }

    public static void gotoNextKey() {
        if (current >= 99)
            current = 0;
        else
            current++;
    }

    /////////////
    // Getters //
    /////////////
    public static String getKey() {
        return Integer.toString(keyTable[current]);
    }

    public static String getCurrent() {
        return Integer.toString(current);
    }

}
