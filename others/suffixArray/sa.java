
import java.lang.String;

public class sa {
  private static interface BaseArray {
    public int get(int i);
    public void set(int i, int val);
    public int update(int i, int val);
  }
  private static class CharArray implements BaseArray {
    private char[] m_A = null;
    private int m_pos = 0;
    CharArray(char[] A, int pos) { m_A = A; m_pos = pos; }
    public int get(int i) { return m_A[m_pos + i] & 0xffff; }
    public void set(int i, int val) { m_A[m_pos + i] = (char)(val & 0xffff); }
    public int update(int i, int val) { return m_A[m_pos + i] += val & 0xffff; }
  }
  private static class IntArray implements BaseArray {
    private int[] m_A = null;
    private int m_pos = 0;
    IntArray(int[] A, int pos) { m_A = A; m_pos = pos; }
    public int get(int i) { return m_A[m_pos + i]; }
    public void set(int i, int val) { m_A[m_pos + i] = val; }
    public int update(int i, int val) { return m_A[m_pos + i] += val; }
  }
  private static class StringArray implements BaseArray {
    private String m_A = null;
    private int m_pos = 0;
    StringArray(String A, int pos) { m_A = A; m_pos = pos; }
    public int get(int i) { return (int)(m_A.charAt(m_pos + i) & 0xffff); }
    public void set(int i, int val) { }
    public int update(int i, int val) { return 0; }
  }

  /* find the start or end of each bucket */
  private static
  void
  getCounts(BaseArray T, BaseArray C, int n, int k) {
    int i;
    for(i = 0; i < k; ++i) { C.set(i, 0); }
    for(i = 0; i < n; ++i) { C.update(T.get(i), 1); }
  }
  private static
  void
  getBuckets(BaseArray C, BaseArray B, int k, boolean end) {
    int i, sum = 0;
    if(end != false) { for(i = 0; i < k; ++i) { sum += C.get(i); B.set(i, sum); } }
    else { for(i = 0; i < k; ++i) { sum += C.get(i); B.set(i, sum - C.get(i)); } }
  }

  /* sort all type LMS suffixes */
  private static
  void
  LMSsort(BaseArray T, int[] SA, BaseArray C, BaseArray B, int n, int k) {
    int b, i, j;
    int c0, c1;
    /* compute SAl */
    if(C == B) { getCounts(T, C, n, k); }
    getBuckets(C, B, k, false); /* find starts of buckets */
    j = n - 1;
    b = B.get(c1 = T.get(j));
    --j;
    SA[b++] = (T.get(j) < c1) ? ~j : j;
    for(i = 0; i < n; ++i) {
      if(0 < (j = SA[i])) {
          if((c0 = T.get(j)) != c1) { B.set(c1, b); b = B.get(c1 = c0); }
        --j;
        SA[b++] = (T.get(j) < c1) ? ~j : j;
        SA[i] = 0;
      } else if(j < 0) {
        SA[i] = ~j;
      }
    }
    /* compute SAs */
    if(C == B) { getCounts(T, C, n, k); }
    getBuckets(C, B, k, true); /* find ends of buckets */
    for(i = n - 1, b = B.get(c1 = 0); 0 <= i; --i) {
      if(0 < (j = SA[i])) {
        if((c0 = T.get(j)) != c1) { B.set(c1, b); b = B.get(c1 = c0); }
        --j;
        SA[--b] = (T.get(j) > c1) ? ~(j + 1) : j;
        SA[i] = 0;
      }
    }
  }
  private static
  int
  LMSpostproc(BaseArray T, int[] SA, int n, int m) {
    int i, j, p, q, plen, qlen, name;
    int c0, c1;
    boolean diff;

    /* compact all the sorted substrings into the first m items of SA
        2*m must be not larger than n (proveable) */
    for(i = 0; (p = SA[i]) < 0; ++i) { SA[i] = ~p; }
    if(i < m) {
      for(j = i, ++i;; ++i) {
        if((p = SA[i]) < 0) {
          SA[j++] = ~p; SA[i] = 0;
          if(j == m) { break; }
        }
      }
    }

    /* store the length of all substrings */
    i = n - 1; j = n - 1; c0 = T.get(n - 1);
    do { c1 = c0; } while((0 <= --i) && ((c0 = T.get(i)) >= c1));
    for(; 0 <= i;) {
      do { c1 = c0; } while((0 <= --i) && ((c0 = T.get(i)) <= c1));
      if(0 <= i) {
        SA[m + ((i + 1) >> 1)] = j - i; j = i + 1;
        do { c1 = c0; } while((0 <= --i) && ((c0 = T.get(i)) >= c1));
      }
    }

    /* find the lexicographic names of all substrings */
    for(i = 0, name = 0, q = n, qlen = 0; i < m; ++i) {
      p = SA[i]; plen = SA[m + (p >> 1)]; diff = true;
      if((plen == qlen) && ((q + plen) < n)) {
        for(j = 0; (j < plen) && (T.get(p + j) == T.get(q + j)); ++j) { }
        if(j == plen) { diff = false; }
      }
      if(diff != false) { ++name; q = p; qlen = plen; }
      SA[m + (p >> 1)] = name;
    }

    return name;
  }

  /* compute SA and BWT */
  private static
  void
  induceSA(BaseArray T, int[] SA, BaseArray C, BaseArray B, int n, int k) {
    int b, i, j;
    int c0, c1;
    /* compute SAl */
    if(C == B) { getCounts(T, C, n, k); }
    getBuckets(C, B, k, false); /* find starts of buckets */
    j = n - 1;
    b = B.get(c1 = T.get(j));
    SA[b++] = ((0 < j) && (T.get(j - 1) < c1)) ? ~j : j;
    for(i = 0; i < n; ++i) {
      j = SA[i]; SA[i] = ~j;
      if(0 < j) {
        if((c0 = T.get(--j)) != c1) { B.set(c1, b); b = B.get(c1 = c0); }
        SA[b++] = ((0 < j) && (T.get(j - 1) < c1)) ? ~j : j;
      }
    }
    /* compute SAs */
    if(C == B) { getCounts(T, C, n, k); }
    getBuckets(C, B, k, true); /* find ends of buckets */
    for(i = n - 1, b = B.get(c1 = 0); 0 <= i; --i) {
      if(0 < (j = SA[i])) {
        if((c0 = T.get(--j)) != c1) { B.set(c1, b); b = B.get(c1 = c0); }
        SA[--b] = ((j == 0) || (T.get(j - 1) > c1)) ? ~j : j;
      } else {
        SA[i] = ~j;
      }
    }
  }
  private static
  int
  computeBWT(BaseArray T, int[] SA, BaseArray C, BaseArray B, int n, int k) {
    int b, i, j, pidx = -1;
    int c0, c1;
    /* compute SAl */
    if(C == B) { getCounts(T, C, n, k); }
    getBuckets(C, B, k, false); /* find starts of buckets */
    j = n - 1;
    b = B.get(c1 = T.get(j));
    SA[b++] = ((0 < j) && (T.get(j - 1) < c1)) ? ~j : j;
    for(i = 0; i < n; ++i) {
      if(0 < (j = SA[i])) {
        SA[i] = ~(c0 = T.get(--j));
        if(c0 != c1) { B.set(c1, b); b = B.get(c1 = c0); }
        SA[b++] = ((0 < j) && (T.get(j - 1) < c1)) ? ~j : j;
      } else if(j != 0) {
        SA[i] = ~j;
      }
    }
    /* compute SAs */
    if(C == B) { getCounts(T, C, n, k); }
    getBuckets(C, B, k, true); /* find ends of buckets */
    for(i = n - 1, b = B.get(c1 = 0); 0 <= i; --i) {
      if(0 < (j = SA[i])) {
        SA[i] = (c0 = T.get(--j));
        if(c0 != c1) { B.set(c1, b); b = B.get(c1 = c0); }
        SA[--b] = ((0 < j) && (T.get(j - 1) > c1)) ? ~((int)T.get(j - 1)) : j;
      } else if(j != 0) {
        SA[i] = ~j;
      } else {
        pidx = i;
      }
    }
    return pidx;
  }

  /* find the suffix array SA of T[0..n-1] in {0..k-1}^n
     use a working space (excluding T and SA) of at most 2n+O(1) for a constant alphabet */
  private static
  int
  SA_IS(BaseArray T, int[] SA, int fs, int n, int k, boolean isbwt) {
    BaseArray C, B, RA;
    int i, j, b, c, m, p, q, name, pidx = 0, newfs;
    int c0, c1;
    int flags = 0;

    if(k <= 256) {
      C = new IntArray(new int[k], 0);
      if(k <= fs) { B = new IntArray(SA, n + fs - k); flags = 1; }
      else { B = new IntArray(new int[k], 0); flags = 3; }
    } else if(k <= fs) {
      C = new IntArray(SA, n + fs - k);
      if(k <= (fs - k)) { B = new IntArray(SA, n + fs - k * 2); flags = 0; }
      else if(k <= 1024) { B = new IntArray(new int[k], 0); flags = 2; }
      else { B = C; flags = 8; }
    } else {
      C = B = new IntArray(new int[k], 0);
      flags = 4 | 8;
    }

    /* stage 1: reduce the problem by at least 1/2
       sort all the LMS-substrings */
    getCounts(T, C, n, k); getBuckets(C, B, k, true); /* find ends of buckets */
    for(i = 0; i < n; ++i) { SA[i] = 0; }
    b = -1; i = n - 1; j = n; m = 0; c0 = T.get(n - 1);
    do { c1 = c0; } while((0 <= --i) && ((c0 = T.get(i)) >= c1));
    for(; 0 <= i;) {
      do { c1 = c0; } while((0 <= --i) && ((c0 = T.get(i)) <= c1));
      if(0 <= i) {
        if(0 <= b) { SA[b] = j; } b = B.update(c1, -1); j = i; ++m;
        do { c1 = c0; } while((0 <= --i) && ((c0 = T.get(i)) >= c1));
      }
    }
    if(1 < m) {
      LMSsort(T, SA, C, B, n, k);
      name = LMSpostproc(T, SA, n, m);
    } else if(m == 1) {
      SA[b] = j + 1;
      name = 1;
    } else {
      name = 0;
    }

    /* stage 2: solve the reduced problem
       recurse if names are not yet unique */
    if(name < m) {
      if((flags & 4) != 0) { C = null; B = null; }
      if((flags & 2) != 0) { B = null; }
      newfs = (n + fs) - (m * 2);
      if((flags & (1 | 4 | 8)) == 0) {
        if((k + name) <= newfs) { newfs -= k; }
        else { flags |= 8; }
      }
      for(i = m + (n >> 1) - 1, j = m * 2 + newfs - 1; m <= i; --i) {
        if(SA[i] != 0) { SA[j--] = SA[i] - 1; }
      }
      RA = new IntArray(SA, m + newfs);
      SA_IS(RA, SA, newfs, m, name, false);
      RA = null;

      i = n - 1; j = m * 2 - 1; c0 = T.get(n - 1);
      do { c1 = c0; } while((0 <= --i) && ((c0 = T.get(i)) >= c1));
      for(; 0 <= i;) {
        do { c1 = c0; } while((0 <= --i) && ((c0 = T.get(i)) <= c1));
        if(0 <= i) {
          SA[j--] = i + 1;
          do { c1 = c0; } while((0 <= --i) && ((c0 = T.get(i)) >= c1));
        }
      }

      for(i = 0; i < m; ++i) { SA[i] = SA[m + SA[i]]; }
      if((flags & 4) != 0) { C = B = new IntArray(new int[k], 0); }
      if((flags & 2) != 0) { B = new IntArray(new int[k], 0); }
    }

    /* stage 3: induce the result for the original problem */
    if((flags & 8) != 0) { getCounts(T, C, n, k); }
    /* put all left-most S characters into their buckets */
    if(1 < m) {
      getBuckets(C, B, k, true); /* find ends of buckets */
      i = m - 1; j = n; p = SA[m - 1]; c1 = T.get(p);
      do {
        q = B.get(c0 = c1);
        while(q < j) { SA[--j] = 0; }
        do {
          SA[--j] = p;
          if(--i < 0) { break; }
          p = SA[i];
        } while((c1 = T.get(p)) == c0);
      } while(0 <= i);
      while(0 < j) { SA[--j] = 0; }
    }
    if(isbwt == false) { induceSA(T, SA, C, B, n, k); }
    else { pidx = computeBWT(T, SA, C, B, n, k); }
    C = null; B = null;
    return pidx;
  }

  /** Suffixsorting **/
  /* char */
  public static
  int
  suffixsort(char[] T, int[] SA, int n) {
    if((T == null) || (SA == null) || (T.length < n) || (SA.length < n)) { return -1; }
    if(n <= 1) { if(n == 1) { SA[0] = 0; } return 0; }
    return SA_IS(new CharArray(T, 0), SA, 0, n, 65536, false);
  }
  /* String */
  public static
  int
  suffixsort(String T, int[] SA, int n) {
    if((T == null) || (SA == null) ||
       (T.length() < n) || (SA.length < n)) { return -1; }
    if(n <= 1) { if(n == 1) { SA[0] = 0; } return 0; }
    return SA_IS(new StringArray(T, 0), SA, 0, n, 65536, false);
  }

	public static void main(String[] args) {
    int[] SA1, SA2;
    int i,j,k, n1,n2;
		
		String s1 = "aab";
		String s2 = "aab"+"aac";
		
		n1 = s1.length();
    SA1 = new int[n1];
		new sa().suffixsort(s1, SA1, n1);

		n2 = s2.length();
    SA2 = new int[n2];
		new sa().suffixsort(s2, SA2, n2);
		

		for(i = 0; i < n1; i++){
			System.out.println(SA1[i]);
		}
		System.out.println("=====");
		for(i = 0; i < n2; i++){
			System.out.println(SA2[i]);
		}		
	}
}
