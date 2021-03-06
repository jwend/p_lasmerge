/*
===============================================================================

  FILE:  lasreadermerged.hpp
  
  CONTENTS:
  
    Reads LIDAR points from the LAS format from more than one file.

  PROGRAMMERS:

    martin.isenburg@rapidlasso.com  -  http://rapidlasso.com

  COPYRIGHT:

    (c) 2007-2012, martin isenburg, rapidlasso - fast tools to catch reality

    This is free software; you can redistribute and/or modify it under the
    terms of the GNU Lesser General Licence as published by the Free Software
    Foundation. See the LICENSE.txt file for more information.

    This software is distributed WITHOUT ANY WARRANTY and without even the
    implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  
  CHANGE HISTORY:
  
     3 May 2015 -- header sets file source ID to 0 when merging flightlines 
    20 January 2011 -- created missing Livermore and my Extra Virgin Olive Oil
  
===============================================================================
*/
#ifndef LAS_READER_MERGED_HPP
#define LAS_READER_MERGED_HPP

#include "lasreader_las.hpp"
#include "lasreader_bin.hpp"
#include "lasreader_shp.hpp"
#include "lasreader_qfit.hpp"
#include "lasreader_asc.hpp"
#include "lasreader_bil.hpp"
#include "lasreader_dtm.hpp"
#include "lasreader_txt.hpp"

class LASreaderMerged : public LASreader
{
public:

  void set_io_ibuffer_size(I32 io_ibuffer_size);
  inline I32 get_io_ibuffer_size() const { return io_ibuffer_size; };
  BOOL add_file_name(const CHAR* file_name);
  void set_scale_factor(const F64* scale_factor);
  void set_offset(const F64* offset);
  void set_files_are_flightlines(BOOL files_are_flightlines);
  void set_apply_file_source_ID(BOOL apply_file_source_ID);
  void set_translate_intensity(F32 translate_intensity);
  void set_scale_intensity(F32 scale_intensity);
  void set_translate_scan_angle(F32 translate_scan_angle);
  void set_scale_scan_angle(F32 scale_scan_angle);
  void set_parse_string(const CHAR* parse_string);
  void set_skip_lines(I32 skip_lines);
  void set_populate_header(BOOL populate_header);
  void set_keep_lastiling(BOOL keep_lastiling);
  BOOL open();
  BOOL reopen();

  void set_filter(LASfilter* filter);
  void set_transform(LAStransform* transform);

  BOOL inside_tile(const F32 ll_x, const F32 ll_y, const F32 size);
  BOOL inside_circle(const F64 center_x, const F64 center_y, const F64 radius);
  BOOL inside_rectangle(const F64 min_x, const F64 min_y, const F64 max_x, const F64 max_y);

  I32 get_format() const;

  BOOL seek(const I64 p_index){ return FALSE; };

  ByteStreamIn* get_stream() const { return 0; };
  void close(BOOL close_stream=TRUE);

  LASreaderMerged();
  ~LASreaderMerged();

  I64* get_file_point_counts() const
  {
    return file_point_counts;
  }

  void set_file_point_counts(I64* filePointCounts)
  {
    file_point_counts = filePointCounts;
  }

  I32 get_process_count() const
  {
    return process_count;
  }

  I32 get_rank() const
  {
    return rank;
  }

  // mpi
  void populate_rank_points();

  I64* get_file_begin_index() const
  {
    return file_begin_index;
  }

  I64* get_file_end_index() const
  {
    return file_end_index;
  }

  U32 get_file_name_number() const
  {
    return file_name_number;
  }

  CHAR** get_file_names() const
  {
    return file_names;
  }

  I64* get_rank_begin_index() const
  {
    return rank_begin_index;
  }

  I64* get_rank_end_index() const
  {
    return rank_end_index;
  }

  I64* get_rank_point_count() const
  {
    return rank_point_count;
  }

  void mpi_init_range();

  U32 get_file_name_start() const
  {
    return file_name_start;
  }

protected:
  BOOL read_point_default();

private:
  BOOL open_next_file();
  void clean();

  LASreader* lasreader;
  LASreaderLAS* lasreaderlas;
  LASreaderBIN* lasreaderbin;
  LASreaderSHP* lasreadershp;
  LASreaderQFIT* lasreaderqfit;
  LASreaderASC* lasreaderasc;
  LASreaderBIL* lasreaderbil;
  LASreaderDTM* lasreaderdtm;
  LASreaderTXT* lasreadertxt;
  BOOL point_type_change;
  BOOL point_size_change;
  BOOL rescale;
  BOOL reoffset;
  F64* scale_factor;
  F64* offset;
  BOOL files_are_flightlines;
  BOOL apply_file_source_ID;
  F32 translate_intensity;
  F32 scale_intensity;
  F32 translate_scan_angle;
  F32 scale_scan_angle;
  CHAR* parse_string;
  I32 skip_lines;
  BOOL populate_header;
  BOOL keep_lastiling;
  U32 file_name_start; // mpi
  U32 file_name_current;
  U32 file_name_number;
  U32 file_name_allocated;
  I32 io_ibuffer_size;
  CHAR** file_names;
  F64* bounding_boxes;
  // mpi
  I32 rank;
  I32 process_count;
  // arrays indexed by rank id
  I64 *file_point_counts;
  I64 *file_begin_index;
  I64 *file_end_index;

  // files assigned to each process
  CHAR ***rank_file_names;
  I64 **rank_file_names_begin_point;
  I64 **rank_file_names_end_point;
  I32 *rank_file_names_count;
  // global point begin and ends for each process
  I64 *rank_point_count;
  I64 *rank_begin_index;
  I64 *rank_end_index;

};

#endif
