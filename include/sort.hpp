/*
 * sort algorithms
 *
 * Maintainer: glozanoa <glozanoa@uni.pe>
 */

#ifndef _SORT_H
#define _SORT_H

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#include "helper.hpp"
#include "cast.hpp"
//#include "partition.hpp"

//template<typename T>
//typedef vector<int> SortAlgorithm(vector<int>, bool);

template<typename T>
class Sort
{
public:

  ////////////// helper functions /////////////
  // tested - date Apr 15 2021
  static int index_min_element(vector<T> elements,
                               unsigned int min_index, unsigned int max_index,
                               bool verbose)
  /*
   * Return the index of the minimum element of elements vector
   */
  {
    int index; // index of minimum element of elements[min_index:max_index]
    unsigned int length = elements.size();
    if(min_index > max_index)
      index = -1;
    else if (min_index >= length || max_index >= length)
      index = -1;
    else
      {
        index = min_index;
        T smallest = elements[min_index];

        for(int k=min_index; k <= max_index; k++)
          {
            if (elements[k] < smallest)
              {
                smallest = elements[k];
                index = k;
              }
          }
        if (verbose)
          {
            cout << "(Minimum value) index:" << index << ", value:" << smallest << endl;
          }
      }
    return index;
  }

  // tested - date Apr 15 2021
  static int index_min_element(vector<T> elements, unsigned int min_index, bool verbose)
  {
    unsigned int max_index = elements.size() - 1;
    int index = Sort<T>::index_min_element(elements, min_index, max_index, verbose);
    return index;
  }

  // tested - date apr 15 2021
  static void exchange(vector<T>* elements, unsigned int i, unsigned int j)
  /*
   * Exchange element i with element j of elements vector
   */
  {
    unsigned int length = elements->size();

    if (i >= length || j >= length)
      {
        string warning = "Some index out of range"; //: i="; //+ to_string(i) + ", j=" + to_sting(j);
        throw out_of_range(warning.c_str());
      }
    else
      {
        T aux = elements->at(i);
        elements->at(i) = elements->at(j);
        elements->at(j) = aux;
      }
  }

  ////////////// sort algorithms /////////////
  // tested - date Apr 15 2021
  static vector<T> bubble(vector<T> elements, bool verbose)
  /*
   * Sort vector of elements using bubble sort algorithm
   */
  {
    T aux;
    int length = elements.size();
    for(int i=0; i< length - 1; i++)
      {
        for(int j=0; j < length -1 - i; j++)
          {
            if (elements[j] > elements[j+1])
              Sort<T>::exchange(&elements, j, j+1);
          }

        if(verbose)
          {
            cout << "(step " << i << " )" << endl;
            print(elements);
          }
      }
    return elements;
  }

  // tested - date Apr 15 2021
  static vector<T> selection(vector<T> elements, bool verbose)
  /*
   * Sort vector of elements using selection sort algorithm
   */
  {
    for(int i=0; i<elements.size()-1; i++)
      {
        if (verbose)
          cout << "(Iteration " << i << ")" << endl;

        int j = Sort<T>::index_min_element(elements, i, verbose);
        Sort<T>::exchange(&elements, i, j);

        if (verbose)
          print(elements);
      }
    return elements;
  }

  //tested - date Apr 15 2021
  static vector<T> insertion(vector<T> elements, bool verbose)
  /*
   * Sort vector of elements using insertion sort algorithm
   */
  {
    unsigned int length = elements.size();
    T auxi;
    int k;

    for(int i=1; i<length; i++)
      {
        if (verbose)
          cout << "(Iteration " << i - 1  << ")" << endl;

        auxi = elements[i];
        k = i-1;
        while(k >= 0)
          {
            if(auxi < elements[k])
              {
                elements[k+1] = elements[k];
                k--;
              }
            else
              break;
          }
        elements[k+1] = auxi;

        if (verbose)
          print(elements);
      }
    return elements;
  }

  // SOLVE BUG
  static vector<T> binary_insertion(vector<T> elements, bool verbose)
  /*
   * Sort vector of elements using binary insertion sort algorithm
   */
  {
    unsigned int length = elements.size();
    T auxi;
    int k;
    T init, end;
    T midpoint;

    for(int i=1; i<length; i++)
      {
        if(verbose)
          cout << "(Iteration " << i-1 << ")" << endl;

        auxi = elements[i];
        init = 0;
        end = i-1;
        while(init <= end)
          {
            midpoint = (int)((init+end)/2);
            if(auxi < elements[midpoint])
              end = midpoint -1;
            else
              init = midpoint +1;

            if (verbose)
              cout << "init: "<< init << ", midpoint: " << midpoint << ", end: " << end << endl;
          }
        for(k = i-1; i >= end; i--)
          elements[k+1] = elements[k];

        elements[end] = auxi;

        if(verbose)
          print(elements);
      }

    return elements;
  }

  // static vector<T> quicksort(vector<T> elements, vector<T> pivots, bool verbose)//, SortAlgorithm f)
  // {
  //   Partition<T> partition = Partition<T>(pivots, elements);
  //   vector<T> part;

  //   for(int k=0; k < partition.size(); k++)
  //     partition.sort_part(k, verbose, f);
  // }

  // sels: sorted elements
  static vector<T> intercalation(vector<T> sels1, vector<T> sels2, bool verbose)
  {
    vector<T> mix; //intercalated vector

    unsigned int length_sels1 = sels1.size();
    unsigned int length_sels2 = sels2.size();

    unsigned int i =0;
    unsigned int j =0;
    unsigned int k =0;

    while(i < length_sels1 && j < length_sels2)
      {
        if(sels1[i] < sels2[j])
          {
            mix.at(k) = sels1[i];
            i++;
          }
        else
          {
            mix.at(k) = sels1[j];
            j++;
          }
      }

    // coping leftover elements
    if(i < length_sels1)
      {
        for(int r = i; r < length_sels1; r++)
          {
            mix.at(k) = sels1[r];
            k++;
          }
      }
    else
      {
        for(int r = j; r < length_sels2; r++)
          {
            mix.at(k) = sels1[r];
            k++;
          }
      }

    return mix;
  }

  ////////////// extern sort algorithms /////////////

  static void extern_merge(ifstream f1, ifstream f2, string out_name)
  /*
   * meger sorted files
   */
  {
    ofstream out = ofstream(out_name);

    try{
      if(!f1.is_open()){
        string warning = "File f1 didn't open";
        out.close();
        throw ios_base::failure(warning.c_str());
          }
      else if (!f2.is_open()){
        string warning = "File f2 didn't open";
        f1.close();
        out.close();
        throw ios_base::failure(warning.c_str());
          }
      else{
        string aux; // element to read buffer of files f1 and f2
        T r1, r2; // elements to read files f1 and f2

        r1 = readline<T>(f1);
        r2 = readline<T>(f2);

        while (!(f1.eof() || f2.eof()))
          {
            if(r1 <= r2)
              {
                out << r1 << endl;
                r1 = readline<T>(f1);
              }
            else
              {
                out << r2 << endl;
                r2 = readline<T>(f2);
              }
          }

        if(!f1.eof())
          {
            do{
              r1 = readline<T>(f1);
              out << r1 << endl;
            }while(!f1.eof());
          }
        if(!f2.eof())
          {
            do{
              r2 = readline<T>(f2);
              out << r2 << endl;
            }while(!f2.eof());
          }
      }

      f1.close();
      f2.close();
      out.close();
    }

    catch(exception& error){
      if(f1.is_open())
        f1.close();

      if(f2.is_open())
        f2.close();

      if(out.is_open())
        out.close();

      cout << error.what() << endl;
    }
  }
};

#endif // _SORT_H
