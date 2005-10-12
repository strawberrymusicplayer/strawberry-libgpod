/*
 *  Copyright (C) 2005 Christophe Fergeau
 *
 * 
 *  The code contained in this file is free software; you can redistribute
 *  it and/or modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either version
 *  2.1 of the License, or (at your option) any later version.
 *  
 *  This file is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *  
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this code; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 * 
 *  iTunes and iPod are trademarks of Apple
 * 
 *  This product is not supported/written/published by Apple!
 *
 */


#ifndef DB_PHOTO_PARSER_H
#define DB_PHOTO_PARSER_H

#include "itdb.h"

#define iPodSong Itdb_Track

#define IPOD_THUMBNAIL_FULL_SIZE_CORRELATION_ID 1016
#define IPOD_THUMBNAIL_NOW_PLAYING_CORRELATION_ID 1017
#define IPOD_NANO_THUMBNAIL_FULL_SIZE_CORRELATION_ID 1027
#define IPOD_NANO_THUMBNAIL_NOW_PLAYING_CORRELATION_ID 1031


G_GNUC_INTERNAL int ipod_parse_photo_db (const char *filename);
G_GNUC_INTERNAL int ipod_parse_artwork_db (Itdb_iTunesDB *db);
G_GNUC_INTERNAL int ipod_write_artwork_db (Itdb_iTunesDB *db, 
					   const char *mount_point);

G_GNUC_INTERNAL char *ipod_db_get_artwork_db_path (const char *mount_point);
#endif