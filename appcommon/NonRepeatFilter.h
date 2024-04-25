#ifndef __APPCOMMON_NONREPEATFILTER_H__
#define __APPCOMMON_NONREPEATFILTER_H__
#include <map>
#include <cassert>

namespace BGIQD {
    namespace NONREPEAT{

        struct NonRepeatFilter
        {
            void Push( int start , int end )
            {
                if( (int) ranges.size() >= max_count ) return ;
                for( const auto & pair : ranges )
                {
                    int overlap = 0 ;
                    int total = pair.second - pair.first +1 ;
                    if ( pair.first < start )
                        overlap = pair.second - start + 1 ;
                    else 
                        overlap = end - pair.first +1 ;
                    if( overlap > 0  
                    && (float)overlap/(float)total >= overlap_fac )
                        return ;
                }
                ranges[start] = end ;
            }

            bool Pop( int & start , int & end )
            {
                if( ranges.empty() )
                    return false ;
                else
                {
                    auto pair = *ranges.begin() ;
                    start = pair.first ; 
                    end = pair.second ;
                    ranges.erase(ranges.begin());
                    return true ;
                }
            }

            void Init( int max , float overlap_factor, int curr_scaff_id, int curr_gap_id )
            {
                max_count = max ; 
                overlap_fac = overlap_factor ; 
                scaff_id = curr_scaff_id ;
                gap_id = curr_gap_id ;
            }
            int scaff_id;
            int gap_id ;
            private:
            std::map<int , int > ranges;
            int max_count ; 
            float overlap_fac ;
        };
    }
}
#endif
