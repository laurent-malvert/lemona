/*
** This file is part of Lemona.
** Copyright (C) 2008 Kenfe-Mickaël Laventure
**
** The contents of this file are subject to the terms of either the
** GNU General Public License Version 2 ("GPL") or the MIT License
** (collectively, the "License"). You may not use this file except in
** compliance with the License. You can obtain a copy of the License
** at http://www.opensource.org/licenses/gpl-2.0.php and
** http://www.opensource.org/licenses/mit-license.php or GPL.LICENSE
** and MIT.LICENSE. See the License for the specific language
** governing permissions and limitations under the License.
*/

#ifndef _LEMONA_BLADES_H_
# define _LEMONA_BLADES_H_

struct lemona_zest;

int	lemona_blade_integer(struct lemona_zest *zest,
			     bool isExt, int idx, int off,
			     void *fruit1, void *fruit2);

int	lemona_blade_integer64(struct lemona_zest *zest,
			       bool isExt, int idx, int off,
			       void *fruit1, void *fruit2);

/* this is a dual blade */
int	lemona_blade_output_buffer(struct lemona_zest *zest,
				   bool isExt, int idx, int off,
				   void *fruit1, void* fruit2);

/* this is a dual blade */
int	lemona_blade_output_buffer64(struct lemona_zest *zest,
				     bool isExt, int idx, int off,
				     void *fruit1, void* fruit2);
#endif
